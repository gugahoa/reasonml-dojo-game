open Reprocessing;

type t = {
    pos: (int, int),
    color: Reprocessing.colorT
};

let random_color = () => {
    Constants.blue
};

let populate = (_width, _height) => {
   [{
        pos: (0, 0),
        color: random_color()
    }]
}

let draw = (color, env, ~pos, ~width, ~height) => {
    Draw.fill(color, env);
    Draw.rect(~pos, ~width, ~height, env);
}