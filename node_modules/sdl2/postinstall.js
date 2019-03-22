var yauzl = require("yauzl");
var fs = require("fs");
var exec = require("child_process").exec;
var path = require("path");
var https = require('https');

// Helpers
var j = require('path').join;
var exec = require('child_process').exec;

function mkdirp(dir, cb) {
  if (dir === ".") return cb();
  fs.stat(dir, function(err) {
    if (err == null) return cb(); // already exists

    var parent = path.dirname(dir);
    mkdirp(parent, function() {
      // process.stdout.write(dir.replace(/\/$/, "") + "/\n");
      fs.mkdir(dir, cb);
    });
  });
}


//Download and extract/build
var zipFilename;
if (process.platform === 'darwin'){
  zipFilename = 'sdl2-osx-2.0.7.zip'
} else if (process.platform === 'win32'){
  zipFilename = 'sdl2-win-2.0.7.zip'
} else {
  console.error("No pre-built binaries for " + process.platform + ", downloading source");
  zipFilename = 'sdl2-src-2.0.7.zip'
}

https.get('https://github.com/bsansouci/SDL-mirror/releases/download/2.0.7/' + zipFilename, function(res) {
  if (res.statusCode === 302) {
    https.get(res.headers.location, function(res) {
      handleResponse(res);
    });
    return;
  }
  handleResponse(res);
}).on("error", (err) => {
  console.error("Error: "   + err.message);
});
var encoding =  'binary';

function handleResponse(res) {
  res.setEncoding('binary');

  var len = parseInt(res.headers['content-length'], 10);
  var fileStream = fs.createWriteStream(zipFilename, { encoding });
  var downloaded = 0;
  
  // A chunk of data has been recieved.
  res.on('data', (chunk) => {
    downloaded += chunk.length;
    fileStream.write(chunk);
    process.stdout.write("Downloading " + (100.0 * downloaded / len).toFixed(2) + "% " + (downloaded / 1000) + " kb\r");
  });
  
  fileStream.on('finish', function() {
    yauzl.open(zipFilename, {lazyEntries: true}, function(err, zipfile) {
      if (err) throw err;
      var i = 0;
      zipfile.readEntry();
      zipfile.once("close", function(entry) {
        fs.unlink(zipFilename, () => {
          console.log("Unzip successful.                          ")
          // Build if not windows or mac
          if (process.platform !== "darwin" && process.platform !== "win32") {
            console.log("Building from source, will take a minute or two.");
            exec("./configure --prefix=$(pwd) --libdir=$(pwd) --enable-assertions=disabled --disable-haptic --disable-shared --disable-joystick --enable-fast-install --disable-power --disable-filesystem --disable-oss --disable-alsatest --disable-esd --disable-esdtest --disable-esd-shared --disable-arts --disable-arts-shared --disable-nas --disable-nas-shared --disable-sndio --disable-sndio-shared --disable-video-mir && make -j 9 && make install", (error, stdout, stderr) => {
                if (error) {
                  console.error('Failure while building SDL2, error: ' + error);
                  return;
                } else {
                  console.log('Looks like SDL2 built successfully.');
                }
              });
          }
        });
      });
      zipfile.on("entry", function(entry) {
        if (/\/$/.test(entry.fileName)) {
          // directory file names end with '/'
          mkdirp(entry.fileName, function() {
            if (err) throw err;
            zipfile.readEntry();
          });
        } else {
          process.stdout.write("Unzipped " + i + " of "+zipfile.entryCount+" files                  \r");
          mkdirp(path.dirname(entry.fileName), function() {
            zipfile.openReadStream(entry, function(err, readStream) {
              if (err) throw err;
              readStream.on("end", function() {
                i++;
                zipfile.readEntry();
              });
              // Mode roughly translates to unix permissions.
              // See https://github.com/thejoshwolfe/yauzl/issues/57#issuecomment-301847099          
              var mode = entry.externalFileAttributes >>> 16;
              var writeStream = fs.createWriteStream(entry.fileName, {mode, encoding})
              readStream.pipe(writeStream);
            });
          });
        }
      });
    })
  });

  // The whole response has been received. Print out the result.
  res.on('end', function() {
    fileStream.end();
  });
}


// Generate bsconfig
var platformspecificargs = "";
if (process.platform === 'darwin') { // OSX
  // The reason we need to have the -lSDL flag here and not use the bsconfig's
  // static_library field is that SDL2 is a dynamically loaded library. Adding
  // this flag to the linker, it automatically figures out what to do.
  platformspecificargs = 
    `"-framework", "CoreFoundation", "-framework", "CoreAudio", "-framework", "AudioToolbox", "-framework", "CoreVideo", "-framework", "Cocoa", "-framework", "Carbon", "-framework", "IOKit", "-lm", "-liconv", "-lobjc"`;
} else if (process.platform === 'linux') {
  // These may have to be installed globally?
  //   sudo apt-get install mesa-common-dev
  //   sudo apt-get install freeglut3
  //   sudo apt-get install freeglut3-dev
  //   sudo apt-get install libpulseaudio-dev

  platformspecificargs = `"-lm", "-ldl", "-lpthread", "-lrt"`
} else if (process.platform === "win32") {
  platformspecificargs = `"-lopengl32", "-lgdi32", "-lwinmm", "-limm32", "-lole32", "-loleaut32", "-lversion", "-luuid"`;
} else {
  throw new Error("Platform not supported: " + process.platform);
}

var bsconfigjson = `{
  "name": "sdl2",
  "sources": "fake_src",
  "c-linker-flags": [${platformspecificargs}],
  "static-libraries": ["libSDL2.a"],
  "allowed-build-kinds": ["bytecode", "native"],
  "refmt": 3,
}`;

require('fs').writeFileSync(j(__dirname, 'bsconfig.json'), bsconfigjson);
