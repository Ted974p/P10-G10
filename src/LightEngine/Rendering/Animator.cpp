#include "Animator.h"

#include "SpriteSheet.h"
#include "Animation.h"

#include <iostream>

Animator::Animator(SpriteSheet* spritesheet, std::vector<Animation*> animations) {
	this->current = nullptr; this->last = nullptr;
	
	this->blendtree = false;
	this->frameAsTime = 0;

	this->currentAnimation = 0; this->currentBlendTree = 0;
	
	this->animations = animations;
	this->spritesheet = spritesheet;
}

Animator::~Animator() {
	for (int i = 0; i < animations.size(); i++)	{
		free(animations[i]);
	}
}

void Animator::Update(float deltaTime) {
	Animation* animation = blendtree ? Find(blendtrees[currentBlendTree]->GetCurrent()) : animations[currentAnimation];

	if (animation != nullptr) {
		if (last != animation) {
			frameAsTime = float(animation->start);
			last = animation;
		}

		frameAsTime += (deltaTime) * animation->speed;

		if (frameAsTime > animation->end) {
			frameAsTime = float(animation->start);
		}
		spritesheet->current = int(frameAsTime);
		spritesheet->updateViewport();
	}
}

void Animator::AddAnimation(Animation* animation) {
	animations.push_back(animation);
}

void Animator::AddBlendTree(BlendTree* _blendtree) {
	blendtrees.push_back(_blendtree);
}

Animation* Animator::Find(std::string name) {
	Animation* result = nullptr;
	for (int i = 0; i < animations.size(); i++) {
		if (animations[i]->name == name) {
			return animations[i];
			break;
		}
	}

	return result;
}

void Animator::Play(std::string name)
{
	frameAsTime = int(frameAsTime);

	for (int i = 0; i < animations.size(); i++) {
		if (animations[i]->name == name) {
			currentAnimation = i;
			blendtree = false;
			if (frameAsTime < animations[i]->start || frameAsTime > animations[i]->end) {
				frameAsTime = float(animations[i]->start);
			}
			return;
		}
	}
}

void Animator::PlayBlendTree(std::string name) {
	for (int i = 0; i < blendtrees.size(); i++) {
		if (blendtrees[i]->name == name) {
			currentBlendTree = i;
			blendtree = true;
			return;
		}
	}
}