#ifndef ISTATE_HPP
#define ISTATE_HPP

class IState
{
public:
	IState() : quit_(false), pop_(false) {}
	virtual ~IState() {}

	virtual void update(float dt) = 0;
	virtual void render() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	bool quitRequested() { return quit_; }
	bool popRequested() { return pop_; }

protected:
	bool quit_, pop_;
};

#endif