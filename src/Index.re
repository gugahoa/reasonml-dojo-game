open Reprocessing;

type state = {
  grid: Grid.t,
}

let setup = (env) => {
  Env.size(~width=500, ~height=500, env);
  
  {
    grid: Grid.make(10, 10),
  }
};

let draw = (state, env) => {
  Draw.background(Constants.black, env);
  Grid.draw(state.grid, env);

  state
};

let mouseDown = (state, env) => {
  let grid = Grid.click(state.grid, env);
  {
    grid: grid
  }
}

run(~setup, ~draw, ~mouseDown, ());
