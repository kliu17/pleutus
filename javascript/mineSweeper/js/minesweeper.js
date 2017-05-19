// New Game
function newGame(difficulty) {
    // On selection of mode, create corresponding grids.
    switch (difficulty) {
        case 'easy':
            board = new Board(6,8,4);
            break;
        case 'hard':
            board = new Board(30,30,50);
            break;
        case 'reg':
        default:
            board = new Board(30,15,20);
            break;
    }
    board.render();
    board.gameOver = false;
    $('.space').click(function (eventObject) {
        board.click(eventObject.target);
    });
    return board;
}

// Board Object
function Board(row, col, bombCount){
    this.row = row;
    this.col = col;   
    this.spaces = [];    
    this.gameOver = false;
    this.spacesCleared = 0;
    this.bombCount = bombCount;

    this.click = function (target_elem) {
        var row = $(target_elem).attr("data-row");
        var col = $(target_elem).attr("data-col");

        if (this.gameOver === true) {
            return;
        }

        if (this.spaces[row - 1][col - 1].explored == true) {
            return;
        }

        if (this.spaces[row - 1][col - 1].holds == -1) {
            this.explode();
        } else if (this.spaces[row - 1][col - 1].holds == 0) {
            this.clear(row - 1, col - 1);
            uncoverSurroundings.call(this, row - 1, col - 1);
        } else {
            this.clear(row - 1, col - 1);
        }
    }

    this.render = function() {
        var spaces = "";
        for (i = 1; i <= row; i++) {
            for (j = 1; j <= col; j++) {
                spaces = spaces.concat('<div class="space" data-row="' + i + '" data-col="' + j + '">&nbsp;</div>');
            }
            spaces = spaces.concat('<br />');
        }
        $('#board').empty();
        $('#board').append(spaces);
    }

    this.explode = function() {
        for (i = 0; i < this.row; i++) {
            for (j = 0; j < this.col; j++) {
                if (this.spaces[i][j].holds == -1) {
                    var dom_target = 'div[data-row="' + (i + 1) + '"][data-col="' + (j + 1) + '"]';
                    $(dom_target).addClass('bomb');
                    $(dom_target).html('<i class="fa fa-bomb"></i>');
                }
            }
        }
        this.gameOver = true;
        $('#new-game').show();
    }

    var numBombNear = function(row, col) {
        var sum = 0;

        if (this.spaces[row][col].holds == -1) {
            return -1;
        }

        sum += valueAt.call(this, row - 1, col - 1) + valueAt.call(this, row - 1, col) + valueAt.call(this, row - 1, col + 1) 
            + valueAt.call(this, row, col - 1) + valueAt.call(this, row, col + 1) 
            + valueAt.call(this, row + 1, col - 1) + valueAt.call(this, row + 1, col) + valueAt.call(this, row + 1, col + 1);

        return sum;
    }

    function valueAt(row, col) {
        if (row < 0 || row >= this.row || col < 0 || col >= this.col) {
            return 0;
        } else if(this.spaces[row][col].holds == -1){
            return 1;
        } else {
            return 0;
        }
    }

    //Initializing the Object
    if (this.spaces !== undefined) {
        this.spaces = new Array(this.row);

        for (i = 0; i < this.row; i++) {
            this.spaces[i] = new Array(this.col);
            for (j = 0; j < this.col; j++) {
                this.spaces[i][j] = new Space(false, 0);
            }
        }

        var min = 1;
        var max = this.row * this.col;
        $('#value').html(this.bombCount);
        for (i = 0; i < this.bombCount; i++) {
            var bombIndex = Math.round(Math.random() * (max - 1));
            var x = Math.floor(bombIndex / this.col);
            var y = bombIndex % this.col;
            this.spaces[x][y] = new Space(false, -1);
        }

        for (i = 0; i < this.row; i++) {
            for (j = 0; j < this.col; j++) {
                this.spaces[i][j].holds = numBombNear.call(this, i, j);
            }
        }
    }

    this.clear = function (row, col) {
        var dom_target = 'div[data-row="' + (row + 1) + '"][data-col="' + (col + 1) + '"]';
        $(dom_target).addClass('safe');
        if (this.spaces[row][col].holds > 0) {
            $(dom_target).text(this.spaces[row][col].holds);
        } else {
            $(dom_target).html('&nbsp');
        }
        checkAllCellsExplored.call(this);
        this.spacesCleared++;
        this.spaces[row][col].explored = true;
    }

    function checkAllCellsExplored(){
        if (this.row * this.col - this.spacesCleared == this.bombCount) {
            for (i = 0; i < this.row; i++) {
                for (j = 0; j < this.col; j++) {
                    if (this.spaces[i][j].holds == -1) {
                        var bomb_target = 'div[data-row="' + (i + 1) + '"][data-col="' + (j + 1) + '"]';
                        $(bomb_target).html('<i class="fa fa-smile-o"></i>');
                        this.gameOver = true;
                        $('#new-game').show();
                    }
                }
            }
        }
    }

    function uncoverSurroundings(row, col) {
        checkSpace.call(this, row - 1, col - 1); checkSpace.call(this, row - 1, col); checkSpace.call(this, row - 1, col + 1);
        checkSpace.call(this, row, col - 1); checkSpace.call(this, row, col + 1);
        checkSpace.call(this, row + 1, col - 1); checkSpace.call(this, row + 1, col); checkSpace.call(this, row + 1, col + 1);
        checkAllCellsExplored.call(this);
    }

    function checkSpace(row, col) {
        if (row < 0 || row >= this.row || col < 0 || col >= this.col || this.spaces[row][col].explored == true) {
            return;
        } else if (this.spaces[row][col].holds >= 0) {
            this.clear(row, col);
            if (this.spaces[row][col].holds == 0) {
                uncoverSurroundings.call(this, row, col);
                return;
            }
        }
    }
}

//Space Object
function Space(explored, holds){
    this.explored = explored;
    this.holds = holds;
}
