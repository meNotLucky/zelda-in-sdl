# The Legend of Zelda for the NES recreated in C++ using SDL

## About the project

This is a school project from the first year of Game design and programming at Uppsala University.
The specific course is Game Programming 1.

The task was to recreate a classic game in about a month, although since the assignement overlapped the holidays I only worked on
it for about two weeks. All of the source code outside of SDL was written entirely by me. My goal was to create the first four levels of
the original The Legend of Zelda game for the NES, including the starting cave where you retrieve the sword.

### Planning
The Legend of Zelda is a (kind of open world) game with pre-created levels with their own set of enemies. To properly recreate the game in as much detail as possible I started out by:
- Playing the game for a few hours (And getting nowhere cause apparently games used to be a lot harder).
- Observing the mechanics and recreated the process in my mind using the Caligula systems as well as some new ones (And it almost worked)
- Deciding to try to recreate at least the starting level (including the cave) and the 3 levels connected to it.

## Development

### World Transitions
The first thing that came to mind when playing the game was how to do the world transitions. I decided that the easiest way to do this would be to create a “WorldManager” that contained all the levels, each level with it own set of tiles.
The world manager would have all the levels placed out in their respective positions relative to each other and rendered, but only the active level (the one the player is currently in) would render colliders and the enemies for that level. When getting to the edge of a level, the world manager would, for each level, grab all the tiles and simultaneously move all tiles in that direction, to reveal the next level.

![Image](https://i.imgur.com/Yi0lK7E.gif)

### Levels and Tiles
The levels would be created from data gathered from a .txt document with the same name as the ID of each level. Each level would have its own set of Tiles and enemies (Although only the tiles were generated from the Data).
The tiles would only contain their position within the level, a sprite, an enum ‘TileType’, and a collider (If the TileType was of a type that the player would interact with).

![Image](https://i.imgur.com/6CtZYoF.png)

### Player UI and Items
The player would be part of the Game state itself (A decision i would later come to regret). And the user interface would gather data from the player and display in real time.
The ‘pick up’ items would already be part of the player and be represented by Integer or boolean values. They would increment or become true when the player collides with them ingame.

![Image](https://i.imgur.com/hujzRHC.png)

### Enemy AI
Their movement in the original game is peculiar as they do not target the player, but at the same time doesn’t look random. I planned to use A* pathfinding but decided it wasn’t worth the time it would take since I only had a few days left and the movement patterns wouldn’t be very different. I decided to instead do a check every time an enemy has the same coordinates as one of the tiles, and give it a chance to switch direction.

### Collision Handling & Optimizing
This was changed many times but ended up being handled by the active level as all the collisions with enemies and tiles would come directly from the source.

![Image](https://i.imgur.com/0c4jfZa.png)

At first the collision checking would slow down the game significantly. This was because it looped through the entire list of tiles for every level and checked for collisions with the player as well as all the enemies. I managed to optimize it by only giving colliders to and checking the tiles that the enemies and player would actually interact with. I also only checked for collisions in the currently active level.

![Image](https://i.imgur.com/cZQM9LW.png)


## The Result

Overall I'm happy with how the game turned out, while I didn't have time to include things such as item pickups and the bow, I'm proud of the world transitions and other systems that I had time to implement. Feel free to try out the game, there is a finished build in the repository that you can download and launch.
