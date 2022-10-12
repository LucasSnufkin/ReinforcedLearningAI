# Reinforced Learning AI

Chef oeuvre n°2 du projet ZZ1

Made by GAUTIER Lucas, MONTAGNON Tom and BENQUET Matthias

AI using QLearning to learn how to defeat each rooms of our previous Arcade Game that has been tweaked for the project.
Our methods give results for room 0 to room 8 with the exception of room 6 and some problems with low learning time on room 7

For training, We suggest putting :
- nbIterMax= 500  (maybe a lot more if you train on one of the harder room)
- nbRunMax = 1 000 000 (more if you have the time) (the AI should start to learn an effective path at ~250 000 depending on the room)
- salleEntrainement= X (this is the room you want to train on. 1-2-3-4-5 should be the more interesting)
- delaySDL = 100 or 150 (time for the character to move)
- FakeRun = 0 (it's the Debug Mode if you don't want to ruin your Qtables or watch a run with no Qtables)
                            
Compile and Have Fun
