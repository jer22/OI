import pygame,sys
pygame.init()
screen=pygame.display.set_caption('hello world!')
screen=pygame.display.set_mode([640,480])
screen.fill([255,255,255])
pygame.draw.circle(screen,[0,0,0],[-28+100,-55+100],10,10)
pygame.draw.circle(screen,[0,0,0],[1+100,-13+100],10,10)
pygame.draw.circle(screen,[0,0,0],[96+100,12+100],10,10)
pygame.draw.circle(screen,[0,0,0],[31+100,-87+100],10,10)
pygame.draw.circle(screen,[0,0,0],[-22+100,84+100],10,10)
pygame.draw.circle(screen,[0,0,0],[-79+100,53+100],10,10)
pygame.draw.circle(screen,[0,0,0],[74+100,-97+100],10,10)
pygame.draw.circle(screen,[0,0,0],[-63+100,86+100],10,10)
pygame.draw.circle(screen,[0,0,0],[78+100,50+100],10,10)
pygame.draw.circle(screen,[0,0,0],[16+100,-85+100],10,10)
pygame.display.flip()
while (True):
        a=0

