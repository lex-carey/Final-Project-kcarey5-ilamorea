# Final-Project-kcarey5-ilamorea - MINESWEEPER STATS TRACKER + GAME

Most of the work done for this project was in the board class, where logic was implemented for random board generation as well as recursive square cleaning. As far as we know, these methods are fully functional but we are currently unable to display our efforts due to a bug in the board constructor (bad pointer). We did not have time to come up with a fix before the deadline.

Our original proposal placed most of the weight for this project on the random board generation along with recursive square clearing. We would like to propose a new distribution of points:
* Total Project Points: 200
  * 75 points - Random Board Generation. The board class contains a little under 400 lines of code solely related to board generation. This is where the majority of Alexis' efforts were spent.
  * 30 points - Recursive tile clearing for empty squares. This is something that was discussed as a high-value item because of the struggles past students experienced with it. Board's uncoverTile function is where you can see this implemented. If the game was currently functional, we believe this function would work as intended.
  * 10 points - Stats logged after game is played. The logic for doing this is present but it is not currently implemented in engine.cpp.
  * 25 points - Stats able to be viewed on stats screen. Unfortunately this was not something we were able to implement before the deadline.
  * 40 points - Game is playable/program functional. While an obviously important part of the project, we feel we assigned too many points to such a general category so we decided to break it up a little. As mentioned already we currently do not have a functional program.
  * 10 points - All screens (menu, game, stats) are accessible. This is not the case for us right now.
  * 10 points - Tracking time and bombs in corner of game screen

We believe most of our earned points for this project will be from the first two bullet points, as these are the largest parts of the program. Honestly just given a little more time we probably could have gotten it all done. Considering how much is missing from our program, we would put this project at ~100 points.