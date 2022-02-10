#pragma once
#include "Common/d3dApp.h"
#include "Common/MathHelper.h"
#include "Common/UploadBuffer.h"
#include "Common/GeometryGenerator.h"
#include "Common/Camera.h"
#include "Common/FrameResource.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")

// Lightweight structure stores parameters to draw a shape.  This will
// vary from app-to-app.
struct RenderItem
{
	RenderItem() = default;

	// World matrix of the shape that describes the object's local space
	// relative to the world space, which defines the position, orientation,
	// and scale of the object in the world.
	XMFLOAT4X4 World = MathHelper::Identity4x4();

	XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();

	// Dirty flag indicating the object data has changed and we need to update the constant buffer.
	// Because we have an object cbuffer for each FrameResource, we have to apply the
	// update to each FrameResource.  Thus, when we modify obect data we should set 
	// NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
	int NumFramesDirty = gNumFrameResources;

	// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
	UINT ObjCBIndex = -1;

	Material* Mat = nullptr;
	MeshGeometry* Geo = nullptr;

	// Primitive topology.
	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// DrawIndexedInstanced parameters.
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

	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);

	void					update(const GameTimer& gt);
	void					draw() const;
	void					build();

	XMFLOAT3				getWorldPosition() const;
	void					setPosition(float x, float y, float z);
	XMFLOAT3				getWorldRotation() const;
	void					setWorldRotation(float x, float y, float z);
	XMFLOAT3				getWorldScale() const;
	void					setScale(float x, float y, float z);

	XMFLOAT4X4				getWorldTransform() const;
	XMFLOAT4X4				getTransform() const;

	void					move(float x, float y, float z);
protected:
	virtual void			updateCurrent(const GameTimer& gt);
	virtual void			updateChildren(const GameTimer& gt);

	virtual void			drawCurrent() const;
	void					drawChildren() const;
	virtual void			buildCurrent();
	void					buildChildren();

protected:
	Game* game;
	RenderItem* renderer;
//private:
	XMFLOAT3				mWorldPosition;
	XMFLOAT3				mWorldRotation;
	XMFLOAT3				mWorldScaling;
	std::vector<Ptr>		mChildren;
	SceneNode* mParent;
};