// Command Interface provides a executes method
class Command
{
public:
	virtual void execute()=0;
	virtual ~Command() {}
};

//  Receiver
class Light
{
public:
	void on()
	{}

	void off()
	{}
};

// Concrete Commands
class LightOnCommand : public Command
{
private:
	Light* light;

public:
	LightOnCommand(Light* light): light(light) {}

	void execute()
	{
		light->on()
	}
};


//Concrete Commands
class LightOffCommand : public Command
{
private:
	Light* light;

public:
	LightOffCommand(Light* light): light(light) {}
	
	void execute()
	{
		light->off()
	}
};

// Invoker 
class RemoteControl
{
private:
	Command* command;

public:
	void setCommand(Command* cmd)
	{
		command = cmd;
	}
	
	void pressButton()
	{
		command->execute();
	}	
};

int main()
{
	Light* livingRoomLight = new Light();
	
	Command* lightOn = new LightOnCommand(livingRoomLight);
	Command* lightOff = new LightOffCommand(livingRoomLight);

	RemoteControl* remote = new RemoteControl();
	remote->setCommand(lightOn);
	remote->pressButton();
}

