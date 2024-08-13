import neat
from neat.config import os
from build.m_handle import *



def evaluate_genome(genomes, config):
    ''' 
     
    runs the simulation of the current population of
    blocks and sets their fitness based on the distance they
    reach in the game.
    
    '''

    global WIN ,gen

    win = WIN
    gen+=1

    ge = []
    nets = []
    npcs = []

    for genome_id, genome in genomes:
        genome.fitness = 0
        net = neat.nn.FeedForwardNetwork.create(genome, config)
        nets.append(net)

        npc = PyPlayer()
        npc.spawn()
        npcs.append(npc)

        ge.append(genome)

    objects = [PyObjects(2)]

    obj_ind = 0

    run = True
    while run and len(npcs) > 0:

        # create a enven that allows to leave

        if len(npcs) > 0:
            if len(objects) > 1 and npcs[0].get_position().x > objects[0].get_position().x + objects[0].get_width():
                obj_ind = 1
            else:
                run = False

        for x, npc in enumerate(npcs):
            ge[x].fitness +=0.1
            npc.move()

            output = nets[npcs.index(npc)].activate( npc.get_position().x, abs(npc.get_position().x - obj.get_position().x) )

            if output[0] > 0.5:
                npc.jump()


        add_obj = False

        for obj in objects:
            for npc in npcs:
                if obj.getId() == 2 or obj.getId() == 3:
                   if collision(npc, obj):
                       ge[npcs.index(npc)].fitness -=1
                       nets.pop(npcs.index(npc))
                       ge.pop(npcs.index(npc))
                       npcs.pop(npcs.index(npc))
                else:
                    if collisions2(npc,obj):
                         ge[npcs.index(npc)].fitness -=1
                         nets.pop(npcs.index(npc))
                         ge.pop(npcs.index(npc))
                         npcs.pop(npcs.index(npc))



                if npc.get_position().x > obj.get_position().x :
                    add_obj = True


        if add_obj:
            score +=1

            for genome in ge:
                genome.fitness += 5


        for npc in npcs:
            if npc.get_position().x + npc.get_sprite().get_position() - 10 >= 575 or npc.get_position().y < -50:
                nets.pop(npcs.index(npc))
                ge.pop(npcs.index(npc))
                npcs.pop(npcs.index(npc))


        createGame()


    




#load configuration file and setup neat
def run(config_path):
    ''' 
     
    runs the NEAT algorithm to train a neural network to play geometry dash.
    :param config_file: location of config file
    :return: None
    
    '''

    config = neat.config.Config(neat.DefaultGenome, neat.DefaultReproduction,
                         neat.DefaultSpeciesSet, neat.DefaultStagnation,
                         config_path) #defining all subheadings in file and reads it so can use configuration for a pop


    pop = neat.Population(config) # create a pop

    #adding stats report on each generation

    pop.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    pop.add_reporter(stats)
    winner = pop.run(evaluate_genome, 50) #number is of times we will run fitness function

    
    print('\nBest genome:\n{s}'.format(winner))

    


if __name__ == "__main__":
    local_dir = os.path.dirname(__file__) # this help get dir we are currently in 
    config_path = os.path.join(local_dir, "Configuration.txt")  # join the local directory to name of config file. Absolute path
    run(config_path)
