import numpy as np 
import pygame 
import sys
import math


jony = 'just making sure it work'

BLUE = (0,0,255)
YELLOW = (255,255,0)
BLACK = (0,0,0)
RED = (255,0,0)

#Declare GLOBAL VARIABLE for board size 
ROW_COUNT = 6
COLUMN_COUNT = 7

#Function to create table 
def createBoard():
    board = np.zeros((ROW_COUNT, COLUMN_COUNT))
    return board 

#Drop a piece. 
#Parse parameters 
def dropPiece(board, row, column, piece):
    board[row][column] = piece


#check if valid location 
#IMPORTANT
#NEeds to be edited because if a column if full a piece cannot be dropped there
def is_ValidLocation(board, column):
    return board[ROW_COUNT-1][column] == 0


def get_NextOpenRow(board, column):
    for row in range(ROW_COUNT):
        if board[row][column] == 0:
            return row

def printBoard(board):
    print(np.flip(board,0))

def winningMove(board, piece):
    # Check horizontal locations for win
    for c in range(COLUMN_COUNT-3):
        for r in range(ROW_COUNT):
            if board[r][c] == piece and board[r][c+1] == piece and board[r][c+2] == piece and board[r][c+3] == piece:
                return True
 
    # Check vertical locations for win
    for c in range(COLUMN_COUNT):
        for r in range(ROW_COUNT-3):
            if board[r][c] == piece and board[r+1][c] == piece and board[r+2][c] == piece and board[r+3][c] == piece:
                return True
 
    # Check positively sloped diaganols
    for c in range(COLUMN_COUNT-3):
        for r in range(ROW_COUNT-3):
            if board[r][c] == piece and board[r+1][c+1] == piece and board[r+2][c+2] == piece and board[r+3][c+3] == piece:
                return True
 
    # Check negatively sloped diaganols
    for c in range(COLUMN_COUNT-3):
        for r in range(3, ROW_COUNT):
            if board[r][c] == piece and board[r-1][c+1] == piece and board[r-2][c+2] == piece and board[r-3][c+3] == piece:
                return True

def draw_board(board):
    for c in range(COLUMN_COUNT):
        for r in range(ROW_COUNT):
            pygame.draw.rect(screen, BLUE, (c*SQUARESIZE, r*SQUARESIZE+SQUARESIZE, SQUARESIZE, SQUARESIZE))
            pygame.draw.circle(screen, BLACK, (int(c*SQUARESIZE+SQUARESIZE/2), int(r*SQUARESIZE+SQUARESIZE+SQUARESIZE/2)), RADIUS)
     
    for c in range(COLUMN_COUNT):
        for r in range(ROW_COUNT):      
            if board[r][c] == 1:
                pygame.draw.circle(screen, RED, (int(c*SQUARESIZE+SQUARESIZE/2), height-int(r*SQUARESIZE+SQUARESIZE/2)), RADIUS)
            elif board[r][c] == 2: 
                pygame.draw.circle(screen, YELLOW, (int(c*SQUARESIZE+SQUARESIZE/2), height-int(r*SQUARESIZE+SQUARESIZE/2)), RADIUS)
    pygame.display.update()

SQUARESIZE = 100
RADIUS = int(SQUARESIZE/2 - 5)

width = COLUMN_COUNT * SQUARESIZE
height = (ROW_COUNT+1) * SQUARESIZE

size = (width, height)
screen = pygame.display.set_mode(size)

def startGame():

    board = createBoard()
    printBoard(board)
    game_over = False
    turn = 0
    
    #initalize pygame
    pygame.init()
    
    #define our screen size
    SQUARESIZE = 100
    
    #define width and height of board

    

    
    RADIUS = int(SQUARESIZE/2 - 5)
    
    
    #Calling function draw_board again
    draw_board(board)
    pygame.display.update()
    
    myfont = pygame.font.SysFont("monospace", 75)
    
    while not game_over:
        # Add prompt to tell us 
    
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
    
            if event.type == pygame.MOUSEMOTION:
                pygame.draw.rect(screen, BLACK, (0,0, width, SQUARESIZE))
                posx = event.pos[0]
                if turn == 0:
                    pygame.draw.circle(screen, RED, (posx, int(SQUARESIZE/2)), RADIUS)
                else: 
                    pygame.draw.circle(screen, YELLOW, (posx, int(SQUARESIZE/2)), RADIUS)
            pygame.display.update()
    
            if event.type == pygame.MOUSEBUTTONDOWN:
                pygame.draw.rect(screen, BLACK, (0,0, width, SQUARESIZE))
                #print(event.pos)
                # Ask for Player 1 Input
                if turn == 0:
                    posx = event.pos[0]
                    col = int(math.floor(posx/SQUARESIZE))

                    if is_ValidLocation(board, col) == False:
                        print("not possible mate")
                        label = myfont.render("INVALID MOVE", 1, RED)
                        screen.blit(label, (30,10))
                        turn -= 1
                        
                    else:   
                        row = get_NextOpenRow(board, col)
                        dropPiece(board, row, col, 1)

                        if winningMove(board, 1):
                            label = myfont.render("Player 1 wins!!", 1, RED)
                            screen.blit(label, (40,10))
                            game_over = True
                    
    
    
                # # Ask for Player 2 Input
                else:               
                    posx = event.pos[0]
                    col = int(math.floor(posx/SQUARESIZE))
    
                    if is_ValidLocation(board, col) == False:
                        print("not possible mate")
                        label = myfont.render("INVALID MOVE", 1, YELLOW)
                        screen.blit(label, (30,10))
                        turn -= 1
                    
                    else:
                        row = get_NextOpenRow(board, col)
                        dropPiece(board, row, col, 2)
    
                        if winningMove(board, 2):
                            label = myfont.render("Player 2 wins!!", 1, YELLOW)
                            screen.blit(label, (40,10))
                            game_over = True
                
    
                printBoard(board)
                draw_board(board)
    
                turn += 1
                turn = turn % 2
    
                if game_over:
                    pygame.time.wait(3000)