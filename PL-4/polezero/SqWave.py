import pygame,time
pygame.init()
MaxLen=640
MaxWid=480
screen = pygame.display.set_mode((MaxLen, MaxWid))
running = 1
WHITE=(255, 255, 255)
BLUE=(0,0,255)
AMP=raw_input("Enter The Amplitude : ")
AMMP=int(AMP)
AMMP=AMMP*20
i=20
FQ=raw_input("Enter The Frequency : ")
FRQ=int(FQ)
INCC=((MaxLen/2)-30)/FRQ
lp=0
pygame.draw.line(screen,BLUE,(20,(MaxWid/2)-1),(MaxLen-1,(MaxWid/2)-1))
pygame.draw.line(screen,BLUE,(20,(MaxWid/2)-1),(20,0))
myfont = pygame.font.SysFont("monospace", 15)
label = myfont.render(AMP, 1, (255,255,0))
screen.blit(label, (5,MaxWid/2-AMMP ))
label1=myfont.render("Amplitude", 1, (255,255,0))
screen.blit(label1,( 25,10 ))
lb2=myfont.render("Time", 1, (255,255,0))
lb3=myfont.render("Frequency : "+FQ, 1, (255,255,0))
while(lp<FRQ):
	pygame.draw.line(screen, WHITE, (i,MaxWid/2), (i+INCC, MaxWid/2))
	pygame.draw.line(screen, WHITE, (i+INCC,MaxWid/2), (i+INCC,MaxWid/2-AMMP))
	pygame.draw.line(screen, WHITE, (i+INCC,MaxWid/2-AMMP),(i+(2*INCC),MaxWid/2-AMMP))
	pygame.draw.line(screen, WHITE, (i+(2*INCC),MaxWid/2-AMMP),(i+(2*INCC),MaxWid/2))
	lp=lp+1
	i=i+2*INCC
screen.blit(lb2,(MaxLen-50, (MaxWid/2)+10))
screen.blit(lb3,(50, (MaxWid/2)+50))
pygame.display.flip()
time.sleep(100)

