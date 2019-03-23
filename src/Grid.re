open Reprocessing;

module PosMap = Map.Make({
    type t = (int, int);
    let compare = compare;
});

type t = {
    colors: PosMap.t(Reprocessing.colorT),
    horizontal: int,
    vertical: int
};

let colors = [Constants.blue, Constants.green, Constants.white, Constants.red];

let random_color = () => {
    List.nth(colors, Random.int(List.length(colors)))
};

/**
 * Create a list of length `~length` where each
 * element is `~element`.
 */
let rec fill = (length, f: (int) => 'a) =>
  if (length <= 0) {
    [];
  } else {
    [f(length), ...fill(length-1, f)];
  };

let make = (horizontal, vertical) => {
    let colors = ref(PosMap.empty);
    let _useless = fill(horizontal, (x) => {
        fill(vertical, (y) => {
            colors := PosMap.add((x - 1, y - 1), random_color(), colors^)
        })
    });

    {
        colors: colors^,
        horizontal,
        vertical
    }
}

let horizontal = (grid) => {
    grid.horizontal
}

let vertical = (grid) => {
    grid.vertical
}

let draw = (grid, env) => {
    let horizontal = horizontal(grid)
    let vertical = vertical(grid);

    let width = Env.width(env) / horizontal;
    let height = Env.height(env) / vertical;

    PosMap.iter(((pos_x, pos_y), color) => {
        Square.draw(color, env, ~pos=(pos_x * width, pos_y * height), ~width, ~height)
    }, grid.colors)
}

let updateNeighbors = (grid, pos, env) => {
    let horizontal = horizontal(grid)
    let vertical = vertical(grid);

    let width = Env.width(env) / horizontal;
    let height = Env.height(env) / vertical;

    
}

let update = (grid, pos) => {
    PosMap.add(pos, Constants.black, grid.colors);
}

let click = (grid, env) => {
    let horizontal = horizontal(grid)
    let vertical = vertical(grid);

    let width = Env.width(env) / horizontal;
    let height = Env.height(env) / vertical;

    let (x, y) = Env.mouse(env);

    let pos = ((x / width), (y / height))

    let colors = update(grid, pos);

    {
        ...grid, 
        colors
    }
}