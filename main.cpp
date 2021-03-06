#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
//#include <DirectXMath.h>
#include <vector>
#include <string>
#include <math.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include "Input.h"
#include <wrl.h> // 7-1
#include <d3dx12.h>//7-3
#include<xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include<fstream>

#include "Object3d.h"

#include "Win.h"
#include "DirectXCommon.h"
#include "CollisionBase.h"
#include "Collision.h"

#include "Sprite.h"
#include "SpriteCommon.h"
#include <algorithm>

#include "DebugText.h"

#include "Audio.h"

#include "fbxsdk.h"
#include "LoadFbx.h"

#include "Object3dFbx.h"
#include "Camera.h"

#include "PostEffect.h"


#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
//#pragma comment(lib, "DirectXTex.lib")

using namespace Microsoft::WRL;

using namespace DirectX;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{


// WindowsAPI初期化処理
	
	
	Win* win = nullptr;
	Input* input = nullptr;
	DirectXCommon* dxcommon = nullptr;
	Audio* audio = nullptr;

	win = new Win();
	win->WinCreate();


	dxcommon = new DirectXCommon();
	dxcommon->Init(win);

	SpriteCommon* spriteCommon = new SpriteCommon;
	spriteCommon->Init(dxcommon->GetDev(), dxcommon->GetCmdlist(), win->window_width, win->window_height);

	DebugText* debugtext_minute = nullptr;
	debugtext_minute = new DebugText();

	Object3d::StaticInitialize(dxcommon->GetDev(), win->window_width, win->window_height);

	Object3dFbx::SetDevice(dxcommon->GetDev());

	Camera* camera;
	camera = new Camera();
	camera->Init();

	Object3dFbx::SetCamera(camera);

	Object3dFbx::CreateGraphicsPipeline();

	audio = new Audio();
	audio->Init();

	input = new Input();
	input->Initialize(win);

	FbxManager* fbxManager = FbxManager::Create();

	LoadFbx::GetInstance()->Init(dxcommon->GetDev());

	PostEffect* postEffect = nullptr;

	// DirectX初期化処理　ここまで

	//描画初期化処理　ここから
	spriteCommon->LoadTexture(0, L"Resource/background.png");

	Sprite *sprite = Sprite::Create(spriteCommon,0);

	const int debugTextTexNumber3 = 4;

	spriteCommon->LoadTexture(debugTextTexNumber3, L"Resource/ASC_White.png");

	debugtext_minute->debugTextInit(spriteCommon, debugTextTexNumber3);

	DebugText* debugtext_minute2 = nullptr;
	debugtext_minute2 = new DebugText();

	const int debugTextTexNumber4 = 5;

	spriteCommon->LoadTexture(debugTextTexNumber4, L"Resource/ASC_White.png");
	debugtext_minute2->debugTextInit(spriteCommon, debugTextTexNumber4);

	//ポストエフェクト
	//spriteCommon->LoadTexture(100, L"Resource/mimikkyu.jpg");

	postEffect = new PostEffect();
	postEffect->Init(spriteCommon,100, { 0.5f,0.5f }, false, false);


	//音声読み込み
	audio->LoadWave("powerdown07.wav");

	


#pragma region model
	
	ModelFbx* modelFbx = nullptr;
	Object3dFbx* object1 = nullptr;

	modelFbx = LoadFbx::GetInstance()->LoadModelFile("boneTest");
	object1 = new Object3dFbx;
	object1->Init();
	object1->SetModelFbx(modelFbx);


	//Object3d* object3d_camera = nullptr;

	Model* model1 = Model::LoadFromOBJ("car1");
	//Model* model3 = Model::LoadFromOBJ("home3-0");
	//Model* model4 = Model::LoadFromOBJ("ene-0");
	//Model* model5 = Model::LoadFromOBJ("road");
	//Model* model7 = Model::LoadFromOBJ("home_white");
	//Model* model8 = Model::LoadFromOBJ("home_long");
	//Model* model9 = Model::LoadFromOBJ("glass");



	////自機
	Object3d* object3d_player = object3d_player->Create();

	object3d_player->SetModel(model1);

	object3d_player->SetPosition({ 0,-10,-20 });
	object3d_player->rotation.y = -90;
	////道
	//Object3d* object3d_roadCenter = object3d_roadCenter->Create();
	//Object3d* object3d_roadCenter2 = object3d_roadCenter2->Create();
	//Object3d* object3d_roadCenter3 = object3d_roadCenter3->Create();

	//object3d_roadCenter->SetModel(model5);
	//object3d_roadCenter2->SetModel(model5);
	//object3d_roadCenter3->SetModel(model5);

	//object3d_roadCenter->SetPosition({ 0,-30,0 });
	//object3d_roadCenter->scale.z = 200;
	//object3d_roadCenter->scale.x = 20;

	//object3d_roadCenter2->SetPosition({ 0,-30,+800 });//z 400
	//object3d_roadCenter2->scale.z = 200;
	//object3d_roadCenter2->scale.x = 20;

	//object3d_roadCenter3->SetPosition({ 0,-30,+1600 });//z 400
	//object3d_roadCenter3->scale.z = 200;
	//object3d_roadCenter3->scale.x = 20;
	////家
	//Object3d* object3d_home = object3d_home->Create();
	//Object3d* object3d_homeWhite = object3d_homeWhite->Create();
	//Object3d* object3d_homeLong = object3d_homeLong->Create();

	//object3d_home->SetModel(model3);
	//object3d_homeWhite->SetModel(model7);
	//object3d_homeLong->SetModel(model8);

	//object3d_home->SetPosition({ -70,-10,0 });
	//object3d_home->rotation.y = 270;
	//object3d_homeWhite->SetPosition({ 90,-30,30 });
	//object3d_homeWhite->rotation.y = 90;
	//object3d_homeLong->SetPosition({ -90,-30,60 });
	//object3d_homeLong->rotation.y = 270;

	////敵
	//Object3d* object3d_eneCenter = object3d_eneCenter->Create();

	//object3d_eneCenter->SetModel(model4);

	//object3d_eneCenter->SetPosition({ 0,-15,+200 });

	//Object3d* object3d_eneLeft = object3d_eneLeft->Create();

	//object3d_eneLeft->SetModel(model4);

	//object3d_eneLeft->SetPosition({ 0,-15,+50 });

	//Object3d* object3d_eneRight = object3d_eneRight->Create();

	//object3d_eneRight->SetModel(model4);

	//object3d_eneRight->SetPosition({ 35,-15,+400 });

	////背景
	//Object3d* object3d_glass = object3d_glass->Create();
	//Object3d* object3d_glass2 = object3d_glass2->Create();

	//object3d_glass->SetModel(model9);
	//object3d_glass2->SetModel(model9);

	//object3d_glass->SetPosition({ -50,-30,0 });
	//object3d_glass->scale.x = 200;
	//object3d_glass->scale.z = 200;

	//object3d_glass2->SetPosition({ -50,-30,780 });
	//object3d_glass2->scale.x = 200;
	//object3d_glass2->scale.z = 200;

	//当たり判定　球
	Sphere sphere;

	//当たり判定　三角形
	Triangle triangle_ene2;

	//球の初期値を設定
	sphere.center = XMVectorSet(0, -10, -5, 1);//中心点座標
	sphere.radius = 10.0f;//半径


	//LoadFbx::GetInstance()->LoadModelFile("cube");

#pragma endregion
	//描画初期化処理　ここまで



#pragma region シェーダーの色,初期化


	float xmfloat4_r = 1.0f;
	float xmfloat4_b = 1.0f;
	float xmfloat4_g = 1.0f;
	float xmfloat4_a = 1.0f;

	//float ene_x2 = object3d_eneLeft->position.x;
	//float ene_y2 = object3d_eneLeft->position.y;
	//float ene_z2 = object3d_eneLeft->position.z;


	char moji[64];
	char moji2[64];
	char moji3[64];

	int secound_x = 150;
	int secound_y = 0;
	int secound2_x = 100;
	int secound2_y = 0;


	int timer = 60;
	int secound = 0;
	int secound2 = 0;
	int minute = 0;

	int centerCount = 0;
	int leftCount = 0;
	int rightCount = 0;

	int gameScene = 1;

	sprite->SetPosition({ 0.0f,0.0f,0.0f });
	sprite->SetTexsize({1280.0f,720.0f });

	sprite->TransVertexBuffer();

	XMFLOAT3 eye = camera->GetEye();
	
#pragma endregion

	object1->PlayAnimation();
	while (true)  // ゲームループ
	{
		//// メッセージがある？
		

		//// ?ボタンで終了メッセージが来たらゲームループを抜ける

		if (win->ProcessMessage()) {
			break;
		}

		// DirectX毎フレーム処理　ここから

		//キーボード情報の取得開始
		//全キーの入力状態を取得する
		input->Update();

		sprite->Update();

		
		

			//camera->SetEye(eye);
			//camera->SetTarget({ 0,-20,0 });
			XMVECTOR moveZ = XMVectorSet(0, 0, 1.0f, 0);//z speed

			XMVECTOR moveX2 = XMVectorSet(1.0f, 0, 0, 0);//debug

		
			XMFLOAT3 xCamera = { 1,0,0 };
		
			XMFLOAT3 yCamera = { 0,1,0 };
			
			XMFLOAT3 zCamera = { 0,0,1 };
			


			if (input->isKey(DIK_W))
			{
				camera->CameraMoveVector(yCamera,true);//カメラを動かす
			}
			if (input->isKey(DIK_D))
			{
				camera->CameraMoveVector(xCamera,true);//カメラを動かす
			}
			if (input->isKey(DIK_A))
			{
				camera->CameraMoveVector(xCamera,false);//カメラを動かす
			}
			if (input->isKey(DIK_S))
			{
				camera->CameraMoveVector(yCamera,false);//カメラを動かす
			}
			if (input->isKey(DIK_Q))
			{
				camera->CameraMoveVector(zCamera,false);
			}
			if (input->isKey(DIK_E))
			{
				camera->CameraMoveVector(zCamera,true);
			}

			//三角形の初期値を設定
			//triangle_ene2.p0 = XMVectorSet(ene_x2 - 1.0f, ene_y2, ene_z2, 1);//左手前
			//triangle_ene2.p1 = XMVectorSet(ene_x2, ene_y2, ene_z2 + 5.0f, 1);//左奥
			//triangle_ene2.p2 = XMVectorSet(ene_x2 + 1.0f, ene_y2, ene_z2, 1);//右手前
			//triangle_ene2.normal = XMVectorSet(0.0f, 1.0f, 0.0f, 0);//上向き

			bool hit_left = Collision::CheckSphere2Triangle(sphere, triangle_ene2);


			sprintf_s(moji, "%2.1f", camera->GetEyex());
			sprintf_s(moji2, "%2.1f", camera->GetEyey());
			sprintf_s(moji3, "%2.1f", camera->GetEyez());
		


	//当たり判定
			if (hit_left)
			{
				audio->PlayWave("powerdown07.wav");
			}

//秒数カウント
			timer--;
			if (timer <= 0)
			{
				secound++;
				if (secound >= 10)
				{
					secound2++;
					secound = 0;

				}
				if (secound2 >= 6)
				{
					minute++;
					secound2 = 0;
				}
				timer = 60;

			}
			debugtext_minute->Print( moji, secound_x, secound_y, 1.0f);
			debugtext_minute2->Print(moji2, secound2_x, secound2_y + 60, 1.0f);
			debugtext_minute2->Print(moji3, secound2_x, secound2_y + 110, 1.0f);
			object3d_player->Update();
		camera->UpdateCamera();

		object1->Update();

		
		

		//postEffect->PreDrawScene(dxcommon->GetCmdlist());
		
		//object1->Draw(dxcommon->GetCmdlist());
		//postEffect->PostDrawScene(dxcommon->GetCmdlist());
		
		dxcommon->BeginDraw();

		// ４．描画コマンドここから

	

		object1->Draw(dxcommon->GetCmdlist());

		////スプライト共通コマンド
		//postEffect->PreDrawScene(dxcommon->GetCmdlist());
		//spriteCommon->PreDraw();//3-5で消す　パイプラインステートseisei
		//postEffect->Draw(dxcommon->GetCmdlist());
		//sprite->Draw();
		//postEffect->PostDrawScene(dxcommon->GetCmdlist());

		
		
		////スプライト描画
		Object3d::PreDraw(dxcommon->GetCmdlist());
		object3d_player->Draw();
		Object3d::PostDraw();
		//debugtext_minute->DrawAll();
		//debugtext_minute2->DrawAll();
		// ４．描画コマンドここまで
		
		// ５．リソースバリアを戻す

		dxcommon->EndDraw();
		
	}
	// ウィンドウクラスを登録解除
	win->WinFinalize();

	delete modelFbx;
	delete object1;

	delete object3d_player;
	//delete object3d_roadCenter;
	//delete object3d_roadCenter2;
	//delete object3d_roadCenter3;
	//delete object3d_home;
	//delete object3d_homeWhite;
	//delete object3d_homeLong;
	//delete object3d_eneCenter;
	//delete object3d_eneLeft;
	//delete object3d_eneRight;
	//delete object3d_glass;
	//delete object3d_glass2;

	//Audio解放
	audio->Finalize();
	delete audio;

	//デバッグテキスト解放
	delete postEffect;

	debugtext_minute->Finalize();
	delete debugtext_minute;

	delete sprite;
	delete spriteCommon;
	LoadFbx::GetInstance()->Finalize();
	delete dxcommon;
	delete input;
	
	return 0;
}