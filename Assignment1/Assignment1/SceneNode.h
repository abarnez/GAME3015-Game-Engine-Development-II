#pragma once
#include "Common/d3dApp.h"
#include "Common/MathHelper.h"
#include "Common/UploadBuffer.h"
#include "Common/GeometryGenerator.h"
#include "Common/Camera.h"
#include "Common/FrameResource.h"
#include "Category.h"
#include "Command.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")

struct Command;

struct RenderItem
{
	RenderItem() = default;

	XMFLOAT4X4 World = MathHelper::Identity4x4();
	XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();

	int NumFramesDirty = gNumFrameResources;

	UINT ObjCBIndex = -1;

	Material* Mat = nullptr;
	MeshGeometry* Geo = nullptr;

	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	UINT IndexCount = 0;
	UINT StartIndexLocation = 0;
	int BaseVertexLocation = 0;
};

class Game;

/**
 * @file SceneNode.h
 * @author Abdulhakeem Idris
 * @date 2/9/2022
 * @brief
 * This script is the blueprint for creating a generic SceneNode in the World. Everything that
 * exists in the world exists as a scene node. It contains variables for holding the transform
 * of the scene node object, as well as variables for holding the reference to its children and
 * it's parent scene node. Objects are placed into the World in a tree like structure, starting 
 * from a base scene node.
 */

class SceneNode
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode(Game* game);

	Ptr detachChild(const SceneNode& node);
	void attachChild(Ptr child);
	void update(const GameTimer& gt);
	void onCommand(const Command& command, const GameTimer& gt);
	virtual unsigned int getCategory() const;
	void draw() const;
	void build();
	void move(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setWorldRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
	unsigned int SceneNode::getCategory() const
	{
		return Category::Scene;
	}
	XMFLOAT3 getWorldPosition() const;
	XMFLOAT3 getWorldRotation() const;
	XMFLOAT3 getWorldScale() const;
	XMFLOAT4X4 getWorldTransform() const;
	XMFLOAT4X4 getTransform() const;

protected:
	virtual void updateCurrent(const GameTimer& gt);
	virtual void updateChildren(const GameTimer& gt);
	virtual void drawCurrent() const;
	virtual void buildCurrent();

	void drawChildren() const;
	void buildChildren();

protected:
	Game* game;
	RenderItem* renderer;
	XMFLOAT3 mWorldPosition;
	XMFLOAT3 mWorldRotation;
	XMFLOAT3 mWorldScaling;
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};