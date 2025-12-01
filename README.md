# Final-Project-kcarey5-ilamorea

To-Do:
* Window graphics
  * Board
  * Time elapsed
  * Bombs remaining
  * Start/restart board button
* States for squares
  * Make a tile class
    * state clicked/unclicked (probably bool? initialized to clicked=false)
    * Bool bomb 
    * int value for number of bombs surrounding
* Random generation of board
  * 30x16 squares
  * randomly place 100 bombs -> fill in numbers
  * clicked square + 8 surrounding squares cannot have bombs
* recursive square clearing