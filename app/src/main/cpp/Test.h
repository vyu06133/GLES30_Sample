//
// Created by vyu06133 on 2025/05/26 月.
//

#pragma once
#include "TaskSystem.h"
#include "TaskBase.h"
#include "Vertex.h"
#include "CameraBase.h"
#include "Fsm.h"

struct Test
{
	static inline TaskSystem ts;
	static inline AAssetManager* assetManager;

	class Camera : public CameraBase
	{
		virtual void OnTick(float) override
		{
			auto s = ts->Shader();
			auto ang = glm::radians((float)elapsed * 0.5f);
			mEye = vec3(MyMath::Sin(ang) * 15.0f, 10.0f, MyMath::Cos(ang) * 15.0f);
			mCenter = vec3(0.0f);
			mUp = vec3(0.0f,1.0f,0.0f);
		}
	};

	class Stage : public TaskBase
	{
	public:
		std::vector<VertexPNCT> mPnct;
		virtual void OnTick(float deltaTime) override
		{
			localMatrix = mat4(1.0f);
		}
		virtual void OnCreate() override
		{
			Geometry::GenerateCheckerPlaneZX(&mPnct,vec3(20.0f),vec3(20.0f),vec4(0.1f, 0.1f, 0.1f, 1.0f), vec4(0.9f, 0.9f, 0.9f, 1.0f));
			auto s= ts->Shader();
		}
		virtual void OnDraw() override
		{
			auto s = ts->Shader();
			s.UpdateUniform(s.Model,worldMatrix);
			s.BindVertexBuffer(mPnct.data());
			glDrawArrays(GL_TRIANGLES,0,mPnct.size());
		}
	};

	class Ball : public TaskBase
	{
	public:
		static inline std::vector<VertexPNCT> mPnct;

		vec3 mPos;
		vec3 mAdd;
		FSM mFsm;
		virtual void OnTick(float deltaTime) override
		{
#if 0
			mFsm.SetStateActions({
				{"phase0",[&]() {
					if (input->GetKeyScan(VirtualKey::Enter))
					{
						mFsm.changeState("end");
					}
					else if (input->GetKeyScan(VirtualKey::Space))
					{
						mFsm.changeState("phase1");
						auto inst = GameInstance::GetInstance();
						auto assetPath = std::wstring(L"D:\\Projects\\Win Projects\\DX12UWP\\Assets\\");
						auto filename = assetPath + L"fbx\\Hip Hop Dancing.fbx.lst";
						MyUtil::ReadFileAsync(filename, &buf, &asyncStat);
					}
				}},
			{"phase1", [&]() {
				if(asyncStat.GetStat(100) == asyncStat.READY)
				{
					printf("read done\n");
					puts("================");
					buf.push_back(0);
					puts((char*)buf.data());
					puts("================");
					mFsm.changeState("end");
				}
			}},
			{"end", [&]() {
				TRACE("end");
				mFsm.Finish();
			}}
			});
			mFsm.Run();
#endif
			localMatrix = mat4(1.0f);
			localMatrix[3] = vec4(mPos, 1.0f);

#if 0
			switch ( m_nState )
			{
				case INIT:	// 初期化
				{
					// 出現位置を決定
					switch ( rand() & 3 )
					{
						case 0:
							m_position.x = -STAGE_SIZE;
							m_position.z = ( randu() - 0.5 ) * 1.9 * STAGE_SIZE;
							m_fDirection = randu() * 90.0 + 45.0;
							break;
						case 1:
							m_position.x = STAGE_SIZE;
							m_position.z = ( randu() - 0.5 ) * 1.9 * STAGE_SIZE;
							m_fDirection = randu() * 90.0 + 225.0;
							break;
						case 2:
							m_position.x = ( randu() - 0.5 ) * 1.9 * STAGE_SIZE;
							m_position.z = -STAGE_SIZE;
							m_fDirection = randu() * 90.0 - 45.0;
							break;
						case 3:
							m_position.x = ( randu() - 0.5 ) * 1.9 * STAGE_SIZE;
							m_position.z = STAGE_SIZE;
							m_fDirection = randu() * 90.0 + 135.0;
							break;
					}
					m_position.y = 0.0;

					// アニメーション設定
					m_nMotion = E_STOP;
					m_scene.SetCurrentMotion( m_nMotion );
					m_nStep = m_scene.GetStartFrame();

					// 状態遷移
					m_nState = NORMAL;
					return ( TRUE );
				}
				case NORMAL:	// 通常
				{
					if ( m_nMotion != E_WALK )
					{
						// モーションが「移動」でなければ「移動」にする
						m_nMotion = E_WALK;
						m_scene.SetCurrentMotion( m_nMotion );
						m_nStep = m_scene.GetStartFrame();
					}

					// 前進
					m_position.x += sin( rad( m_fDirection ) ) * SPEED_ENEMY_WALK;
					m_position.z += cos( rad( m_fDirection ) ) * SPEED_ENEMY_WALK;

					// 範囲外チェック
					if ( fabs( m_position.x ) > STAGE_SIZE )	m_nState = EXIT;
					if ( fabs( m_position.z ) > STAGE_SIZE )	m_nState = EXIT;
					break;
				}
				case EXIT:	// 範囲外
				{
					return ( FALSE );
				}
				case DAMAGE:	// やられ
				{
					if ( m_nMotion != E_DAMAGE )
					{
						// モーションが「やられ」でなければ「やられ」にする
						m_nMotion = E_DAMAGE;
						m_scene.SetCurrentMotion( m_nMotion );
						m_nStep = m_scene.GetStartFrame();
					}
					else
					{
						// モーションを共有しているのでここで設定が必要
						m_scene.SetCurrentMotion( m_nMotion );
					}
					// モーション終了チェック
					if ( m_nStep + 1 >= m_scene.GetEndFrame() )
						return ( FALSE );
					else
						break;
				}
			}
#endif
		}
		virtual void OnCreate() override
		{
			if (mPnct.size()==0)
			{
//			    Geometry::GenarateCube(&mPnc,vec3(5.0f));
				Geometry::GenerateSphere(&mPnct, 1.0f, 12, 6);
			}
		}
		virtual void OnDraw() override
		{
			auto s = ts->Shader();
			s.UpdateUniform(s.Model,worldMatrix);
			s.BindVertexBuffer(mPnct.data());
			glDrawArrays(GL_TRIANGLES,0,mPnct.size());
		}
	};

	class BallMaster : public TaskBase
	{
	public:
		static const int BALL_COUNT = 100;
		std::vector<VertexPNCT> mPnct;
		std::vector<Ball*> mBalls;
		virtual void OnTick(float deltaTime) override
		{
		}
		virtual void OnCreate() override
		{
			for(auto i=0; i<BALL_COUNT;i++)
			{
				auto b = ts->CreateTask<Ball>(this, "Ball", 1, tickPriority - i);
				mBalls.push_back(b);
			}
		}
	};

	static inline const char* vertex_shader_src =
			"attribute vec3 a_position;\n"
			"attribute vec3 a_normal;\n"
			"attribute vec4 a_color;\n"
			"attribute vec2 a_texcoord;\n"
			"\n"
			"uniform mat4 u_modelMatrix;\n"
			"uniform mat4 u_viewMatrix;\n"
			"uniform mat4 u_projectionMatrix;\n"
			"\n"
			"varying vec4 v_color;\n"
			"varying vec3 v_normal;\n"
			"varying vec2 v_texcoord;\n"
			"\n"
			"void main() {\n"
			"    vec4 worldPos = u_modelMatrix * vec4(a_position, 1.0);\n"
			"    v_normal = mat3(u_modelMatrix) * a_normal;\n"
			"    v_color = a_color;\n"
			"    v_texcoord = a_texcoord;\n"
			"    gl_Position = u_projectionMatrix * u_viewMatrix * worldPos;\n"
			"}\n";

	static inline const char* fragment_shader_src =
			"precision mediump float;\n"
			"\n"
			"varying vec4 v_color;\n"
			"varying vec3 v_normal;\n"
			"varying vec2 v_texcoord;\n"
			"\n"
			"void main() {\n"
			"    gl_FragColor = v_color;\n"
			"    gl_FragColor += vec4(v_texcoord, 1, 1);\n"
			"}\n";


//static inline Shader shader;
static inline mat4 model_;
static inline mat4 view_;
static inline mat4 proj_;
static inline std::vector<VertexPNCT> vpnct;
	static inline void Init()
	{
		auto& s = ts.Shader();
//		auto& s = shader;
		s.Create(vertex_shader_src,fragment_shader_src);
		glUseProgram(s.Program());
		s.ConnectUniformAndSemantics(s.Model, "u_modelMatrix");
		s.ConnectUniformAndSemantics(s.View, "u_viewMatrix");
		s.ConnectUniformAndSemantics(s.Projection, "u_projectionMatrix");
		model_=mat4(1.0f);
		view_=glm::lookAt(vec3(30.f,40.f,50.f)*2.0f,vec3(0.f),vec3(0.f,1.f,0.f));
		proj_=glm::perspective(glm::radians(45.f),2.0f,.1f,10000.f);
		s.UpdateUniform(s.Model,model_);
		s.UpdateUniform(s.View,view_);
		s.UpdateUniform(s.Projection,proj_);
		Geometry::GenerateCheckerPlaneZX(&vpnct,vec3(20.0f),vec3(20.0f),vec4(0.1f, 0.1f, 0.1f, 1.0f), vec4(0.9f, 0.9f, 0.9f, 1.0f));
	}

	static inline void SurfaceChanged(int width, int height)
	{
		auto& s = ts.Shader();
		s.SetScreenSize(width, height);
		glViewport(0, 0, width, height);
	}

	static inline void Touch(int action, int x, int y)
	{
		ts.BroadcastTouch(action,x,y);
	}

	static inline void DrawFrame()
	{
		auto& s = ts.Shader();
		glUseProgram(s.Program());
		ts.Tick(1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ts.Draw();
	}

	static inline void Setup()
	{
		auto c = ts.CreateTask<Camera>(nullptr,"Camera", 0, 0);
		auto s = ts.CreateTask<Stage>(nullptr,"Stage", 1, 1);
		auto b = ts.CreateTask<BallMaster>(nullptr, "BallMaster", 1, BallMaster::BALL_COUNT+1);
	}
};
