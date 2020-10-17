#pragma once

enum class PlayMode {
	End = 0,Loop,Reverse
};

struct Frame {
	float Time;
	Sprite* Image;

	Frame(Sprite* sprite, float time);
	virtual ~Frame();
};

class Clip {
public:
	Clip(PlayMode mode = PlayMode::End, float speed = 1.0f);
	virtual ~Clip();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);
	D3DXVECTOR2 Position() const;

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);
	D3DXVECTOR2 Scale() const;

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3 vec);
	D3DXVECTOR3 Rotation() const;

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3 vec);
	D3DXVECTOR3 RotationDegree() const;

	D3DXVECTOR2 TextureSize() const;

	void AddFrame(Sprite* sprite, float time);

	void Play();
	void Play(UINT startFrame);
	void Stop();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void DrawBound(bool val);

	Sprite* GetSprite();
private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

	float length;
	float speed;

	bool bPlay;
	UINT currentFrame;
	float playTime;

	PlayMode mode;

	vector<Frame*> frames;
};