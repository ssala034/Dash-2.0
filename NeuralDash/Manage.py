import torch
import torch.nn as nn
import neat
import numpy as np

class PyTorchNeuralNetwork(nn.Module):
    def __init__(self, genome, config):
        super(PyTorchNeuralNetwork, self).__init__()
        self.genome = genome
        self.config = config

       
        self.input_keys = config.genome_config.input_keys
        self.output_keys = config.genome_config.output_keys

       
        self.layers = self._create_layers()

    def _create_layers(self):
        
        layers = []
        input_size = len(self.input_keys)
        output_size = len(self.output_keys)

        hidden_size = len(self.genome.nodes) - input_size - output_size
        layers.append(nn.Linear(input_size, hidden_size))
        layers.append(nn.Sigmoid())

        layers.append(nn.Linear(hidden_size, output_size))

        return nn.Sequential(*layers)

    def forward(self, x):
        return self.layers(x)
