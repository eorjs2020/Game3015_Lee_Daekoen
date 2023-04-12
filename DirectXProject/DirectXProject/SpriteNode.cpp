#include "SpriteNode.h"
#include "Game.hpp"

SpriteNode::SpriteNode(Game* mGame) : Entity(mGame)
{
}

void SpriteNode::drawCurrent() const
{
	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = mGame->mCurrFrameResource->ObjectCB->Resource();
	auto matCB = mGame->mCurrFrameResource->MaterialCB->Resource();

	if (renderer != nullptr)
	{
		mGame->getCmdList()->IASetVertexBuffers(0, 1, &renderer->Geo->VertexBufferView());
		mGame->getCmdList()->IASetIndexBuffer(&renderer->Geo->IndexBufferView());
		mGame->getCmdList()->IASetPrimitiveTopology(renderer->PrimitiveType);

		CD3DX12_GPU_DESCRIPTOR_HANDLE tex(mGame->mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		tex.Offset(renderer->Mat->DiffuseSrvHeapIndex, mGame->mCbvSrvDescriptorSize);

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + (UINT64)renderer->ObjCBIndex * objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + (UINT64)renderer->Mat->MatCBIndex * matCBByteSize;

		mGame->getCmdList()->SetGraphicsRootDescriptorTable(0, tex);
		mGame->getCmdList()->SetGraphicsRootConstantBufferView(1, objCBAddress);
		mGame->getCmdList()->SetGraphicsRootConstantBufferView(3, matCBAddress);

		mGame->getCmdList()->DrawIndexedInstanced(renderer->IndexCount, 1, renderer->StartIndexLocation, renderer->BaseVertexLocation, 0);

	}
}

void SpriteNode::buildSprite(std::string MatName, std::string GeoName)
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();

	renderer->World = getTransform();
	renderer->ObjCBIndex = mGame->mAllRitems.size();
	renderer->Mat = mGame->mMaterials[MatName].get();
	renderer->Geo = mGame->mGeometries[GeoName].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	mGame->mRitemLayer[(int)RenderLayer::AlphaTested].push_back(render.get());

	mGame->mAllRitems.push_back(std::move(render));
}

///Used to build an opaque sprite's position, shape and material
void SpriteNode::buildSpriteOpaque(std::string MatName, std::string GeoName)
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();

	renderer->World = getTransform();
	renderer->ObjCBIndex = mGame->mAllRitems.size();
	renderer->Mat = mGame->mMaterials[MatName].get();
	renderer->Geo = mGame->mGeometries[GeoName].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	mGame->mRitemLayer[(int)RenderLayer::Opaque].push_back(render.get());

	mGame->mAllRitems.push_back(std::move(render));
}