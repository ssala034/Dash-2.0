#include "../../hdr/logic/NeuralNet.hpp"
#include <iostream>

namespace gameEngine {
	const sf::Vector2f weightRange = sf::Vector2f(-1.0f, 1.0f);
	const sf::Vector2f biasRange = sf::Vector2f(-1.0f, 1.0f);


	gameEngine::Layer::Layer() {

	}

	gameEngine::Neuron::Neuron() : value(0.0f) {

	}
	gameEngine::NeuralNet::NeuralNet() {

	}

	void gameEngine::NeuralNet::createNetwork(int numOfInputs, int numOfHiddenNeurons) {
		auto getNeuronCount = [&](int layer) -> int {
			return layer == 0 ? numOfInputs : (layer == 1 ? numOfHiddenNeurons : 1);

			};

		for (int layerIndex = 0; layerIndex < 3; layerIndex++) {
			Layer& layer = layers[layerIndex];
			Neuron newNeuron;

			// Each neuron gets weights corresponding to the number of neurons
			// in the next layer. 
			newNeuron.weights = std::vector<float>(getNeuronCount(layerIndex + 1));

			layer.neurons = std::vector<Neuron>(
				getNeuronCount(layerIndex), newNeuron
			);
			// Each layer has biases for the neurons in the next layer. 
			layer.biases = std::vector<float>(getNeuronCount(layerIndex + 1));

		}
	}

	void gameEngine::NeuralNet::randomize() {
		for (Layer& layer : layers) {
			for (Neuron& neuron : layer.neurons) {
				for (float& weight : neuron.weights) {
					weight = randRange(weightRange.x, weightRange.y);
				}


				for (float& bias : layer.biases) {
					bias = randRange(biasRange.x, biasRange.y);
				}

			}
		}
	}

	void gameEngine::NeuralNet::evolve() {
		// to evolve neural network we must variate the biases and weights

		// How far the evolution can mutate values.
		const float evolutionQuotient = 3.0f;

		// How often values are evolved. 
		const int evolutionRate = 4;

		for (Layer& layer : layers) {
			for (Neuron& neuron : layer.neurons) {
				for (float& weight : neuron.weights) {
					if (std::rand() % evolutionRate == 0) {
						weight += randRange(weightRange.x / evolutionQuotient, weightRange.y / evolutionQuotient);

						gameEngine::clamp(weight, weightRange.x, weightRange.y);
					}
				}

				for (float& bias : layer.biases) {
					if (rand() % evolutionRate == 0) {
						bias += randRange(biasRange.x / evolutionQuotient, biasRange.y / evolutionQuotient);

						gameEngine::clamp(bias, biasRange.x, biasRange.y);

					}
				}
			}
		}

	}

	float gameEngine::NeuralNet::predict(const std::vector<float>& inputs) {
		float prediction = 0.0f;

		//might get index out of bounds error
		try {
			const int hiddenLayerNeuronCount = layers[1].neurons.size();
			std::vector<float> neuronValues(hiddenLayerNeuronCount);

			// Sets the values of the input neurons to the given inputs. 
			for (int inputIndex = 0; inputIndex < inputs.size(); inputIndex++) {
				float inputValue = inputs[inputIndex];

				if (inputIndex == 0) {
					inputValue /= 10.0f;
				}
				layers[0].neurons[inputIndex].value = activation(inputValue);

			}

			for (int hiddenNeuronIndex = 0; hiddenNeuronIndex < hiddenLayerNeuronCount; hiddenNeuronIndex++) {
				// Value of current hidden layer neuron. 
				float& neuronValue = neuronValues[hiddenNeuronIndex];
				// Weights of the current hidden layer. 
				std::vector<float> weights;

				for (const Neuron& neuron : layers[0].neurons) {
					weights.push_back(neuron.weights[hiddenNeuronIndex]);
				}

				// Performs the base dot product operation on the inputs and
				// their corresponding weights. 
				neuronValue = dot(inputs, weights);
				// Adds bias to value. 
				neuronValue += layers[0].biases[hiddenNeuronIndex];
				// Normalizes neuron value. 
				neuronValue = activation(neuronValue);
				layers[1].neurons[hiddenNeuronIndex].value = neuronValue;

			}

			// Weights of values for the output layer. 
			std::vector<float> weights;

			for (const Neuron& neuron : layers[1].neurons)
				weights.push_back(neuron.weights[0]);


			// dot product of neuronvalues and weights
			prediction = dot(neuronValues, weights);
			prediction += layers[1].biases[0];
			layers[2].neurons[0].value = activation(prediction);


		}
		catch (std::string& error) {
			std::cout << error << std::endl;
		}

		return activation(prediction);
	}



	float gameEngine::NeuralNet::activation(float value) {
		//using a sigmoid function that maps value between 0 and 1

		return 1.0f / (1 + std::exp(-value));
	}

	float NeuralNet::randRange(sf::Vector2f bounds) {
		return randRange(bounds.x, bounds.y);
	}

	float NeuralNet::randRange(float lowerBound, float upperBound) {
		float value = static_cast<float>(rand() % 1000) / 1000.0f;
		value *= upperBound - lowerBound;
		value += lowerBound;
		return value;
	}


	float gameEngine::NeuralNet::dot(const std::vector<float>& v1, const std::vector<float>& v2) {
		if (v1.size() != v2.size()) {
			throw "NeuralNet Error: Cannot perform dot product, unequal size vectors";
		}

		float result = 0.0f;
		for (int i = 0; i < v1.size(); i++) {
			result += v1[i] * v2[i];
		}
		return result;
	}

	std::vector<std::pair<gameEngine::Player, gameEngine::NeuralNet>> npcs;
	int bestNpcIndex = 0;
	int prvBestNpcIndex = -1;
	bool endGenerationEarly = true;
	float farthestDistance = 0.0f;
	int generations = 0;


	//should work on it later
	sf::Vector2f gameEngine::calculateLastSafeJumpPosition(gameEngine::Player& player, gameEngine::Objects& obj) {
		sf::Vector2f safePosition = player.getPosition();
		bool isInitiallyonGround = player.canJump();

		//create a clone to simulate next steps

		gameEngine::Player isClone = player;

		sf::Clock clock;

		while (isClone.getPosition().x < obj.getPosition().x) {
			sf::Time delta = clock.restart();
			if (isClone.canJump()) {
				float x_new = isClone.getPosition().x + isClone.getVelocity().x * delta.asSeconds();
				// check if new position will generate a collision
				if (obj.getId() == 3 || obj.getId() == 4) {
					if (gameEngine::checkCollision(isClone, obj)) {
						// will crash, so either too far or too close
						(obj.getPosition().x - isClone.getPosition().x > 50) ? x_new += 10.0f : x_new -= 10.0f;

					}
				}
				else {
					if (gameEngine::checkCollisionFromTop(isClone, obj)) {
						//will crash
						(obj.getPosition().x - isClone.getPosition().x > 50) ? x_new += 10.0f : x_new -= 10.0f;
					}
				}
				isClone.update(delta.asSeconds(), obj);
				isClone.setPosition(x_new, isClone.getPosition().y);


			}

			safePosition = isClone.getPosition();
		}

		return safePosition;
	}

	void gameEngine::clamp(float& value, float min, float max) {
		value = std::max(min, std::min(value, max));

	}

	std::pair<gameEngine::Player, gameEngine::NeuralNet>* gameEngine::getFarthestNpc() {
		std::pair<gameEngine::Player, gameEngine::NeuralNet>* nearestNpc = nullptr;

		float distance = 0.0f;

		for (auto& pair : npcs) {
			gameEngine::Player& npc = pair.first;

			if (npc.getPosition().x > distance) {
				nearestNpc = &pair;
				distance = npc.getPosition().x;
			}

		}

		return nearestNpc;

	}

	void gameEngine::initNpcs() {
		npcs.clear();
		bestNpcIndex = 0;
		farthestDistance = 0.0f;

		//Generates 19 npcs for all the other textures
		for (int npcIndex = 0; npcIndex < 19; npcIndex++) {
			gameEngine::Player newNpc;

			newNpc.spawn();

			npcs.push_back(std::make_pair(newNpc, NeuralNet()));

		}

		for (auto& pair : npcs) {
			gameEngine::NeuralNet& neuralNet = pair.second;

			//create network with one input and 3 hidden neurons

			neuralNet.createNetwork(1, 3);
			neuralNet.randomize();
		}

		spawnNpcs();

	}

	void gameEngine::spawnNpcs() {
		for (int npcIndex = 0; npcIndex < npcs.size(); npcIndex++) {
			std::pair<gameEngine::Player, gameEngine::NeuralNet>& pair = npcs[npcIndex];

			gameEngine::Player& npc = pair.first;

			npc.spawn();

		}
	}

	void gameEngine::evolveNpcs() {
		for (int npcIndex = 0; npcIndex < npcs.size(); npcIndex++) {
			std::pair<gameEngine::Player, gameEngine::NeuralNet>& pair = npcs[npcIndex];

			gameEngine::Player& npc = pair.first;
			gameEngine::NeuralNet& neuralNet = pair.second;

			if (npcIndex != bestNpcIndex) {
				neuralNet = npcs[bestNpcIndex].second;
				neuralNet.evolve();
			}
		}
	}


	void gameEngine::updateNpcs(gameEngine::Objects& obj) {
		const float jumpingThreshold = 0.5f;
		sf::Clock clock;

		for (int npcIndex = 0; npcIndex < npcs.size(); npcIndex++) {
			sf::Time delta = clock.restart();
			std::pair<gameEngine::Player, gameEngine::NeuralNet>& pair = npcs[npcIndex];

			gameEngine::Player& npc = pair.first;
			gameEngine::NeuralNet& neuralNet = pair.second;

			const sf::Vector2f safePosition = calculateLastSafeJumpPosition(npc, obj);


			std::vector<float> inputs = {
					std::min(safePosition.x - npc.getPosition().x, 8.0f),
					0.0f,
					obj.getPosition().x
			};

			float prediction = neuralNet.predict(inputs);


			if (prediction > jumpingThreshold) {
				npc.setJump(true);
			}

			npc.update(delta.asSeconds(), obj);

			if (npc.getPosition().x > farthestDistance) {
				farthestDistance = npc.getPosition().x;
				bestNpcIndex = npcIndex;
			}


		}

		int lastNpcAlive = 0;
		int npcsAlive = 0;

		for (int pairIndex = 0; pairIndex < npcs.size(); pairIndex++) {
			auto& pair = npcs[pairIndex];
			gameEngine::Player& npc = pair.first;


			if (npc.isAlive()) {
				lastNpcAlive = pairIndex;
				npcsAlive++;
			}

			if (npcsAlive == 0 || (npcsAlive == 1 && lastNpcAlive == prvBestNpcIndex)) {
				spawnNpcs();
				evolveNpcs();
				generations++;
				prvBestNpcIndex = bestNpcIndex;
			}

		}




	}

	void gameEngine::resetSimulation() {
		initNpcs();
		generations = 1;

	}







}