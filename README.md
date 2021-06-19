# AmongUs 2.0
## How to play this game ?
```
mkdir build
cd build
cmake ..
make
./AmongUs2.0
```

## Key controls
- Arrow keys to move the player.
- press `l` to change the lighting .

# Features
- This is single player 2-D game, Where a player is left in the maze and his mission is to exit the maze after completing the two task keeping in mind there is an imposter (enemy).
- **HUD** - displays
    + **Health** - / Score indicating the players point.
    + **Task** - number of task left.
    + **Light** - whether light is on/off.
    + **Time** - there is a countdown before which player needs to finish the game otherwise game is over.
- **TASKS** 
    + Task1 - It is to press the button red in color to defeat the enemy by vaporizing it.
    + Task2 - It is to press the button yellow in color to release the powerup and obstacles. You need to collect six powerup to finish this task. Each powerup contributes to 2 points and each obstacle deducts 3 points /decreases the health of player.
- **Imposter** - Follows the player in order to kill him by using shortest path algorithm.
- **Light** - using `l` key can switch on/ off the lights. And the player will get `points = seconds spend in light off mode/2.` He will be able to see only the nearby area.

Hope u enjoy playing this game :)
