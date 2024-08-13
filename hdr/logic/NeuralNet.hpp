#pragma once

#include "../gameEngine.hpp"
#include "player.hpp"
#include "objects.hpp"
#include "collisions.hpp"

namespace gameEngine {
	extern const sf::Vector2f weightRange;
	extern const sf::Vector2f biasRange;


	struct Neuron {
		std::vector<float> weights;
		float value;
		Neuron();
	};

	struct Layer {
		std::vector<Neuron> neurons;
		std::vector<float> biases;

		Layer();

	};


	class NeuralNet {
	public:
		//This neural-network has 3 layer. An input, hidden, and output layer
		Layer layers[3];

		NeuralNet();

		void createNetwork(int numOfInputs, int numOfHiddenNeurons);
		void randomize();

		//will mutate next generation
		void evolve();

		//prediction based on inputs
		float predict(const std::vector<float>& inputs);

		//constrains value to either 0 or 1, 
		static float activation(float value);

		static float randRange(sf::Vector2f bounds);
		// Generates value between 2 bounds. Used for generating weights and 
		// biases. 
		static float randRange(float lowerBound, float upperBound);


	private:
		// Performs dot product on 2 vectors. 
		static float dot(const std::vector<float>& v1, const std::vector<float>& v2);


	};

	void clamp(float& value, float min, float max);

	//to keep track of each species one neural-net
	extern std::vector<std::pair<gameEngine::Player, gameEngine::NeuralNet> > npcs;

	// Keeps track of the npc that has made it the furthest. 
	extern int bestNpcIndex;
	extern int prvBestNpcIndex;
	extern bool endGenerationEarly;
	extern float farthestDistance;
	extern int generations;

	// Calculates the last xpos that a player is safe on. 
	sf::Vector2f calculateLastSafeJumpPosition(gameEngine::Player& player, gameEngine::Objects& obj);

	

	std::pair<Player, NeuralNet>* getFarthestNpc();


	void initNpcs();
	void spawnNpcs();
	// Uses best npc to mutate all other npcs. 
	void evolveNpcs();
	void updateNpcs(gameEngine::Objects& obj);
	void resetSimulation();
	

}