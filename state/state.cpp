class TCPState
{
public:
	virtual void open() =0;
	virtual void close()=0;
	virtual void acknowledge()=0;
	virtual ~TCPState(){}	
};


class TCPClosedState : public TCPState
{
public:
	void open() override
	{
		std::cout << "Opening Connection" << endl;
	}

	void close() override
	{
		std::cout << "Connection is already closed" << endl;
	}

	void acknowledge() override
	{
		std::cout << "Can not ack , connection is closed" << endl;
	}	
}; 

class TCPEstablishedState: public TCPState
{
	void open() override
	{
		std::cout << "Connection is already open" << std::endl;
	}

	void close() override
	{
		std::cout << "Closing the connection" << std::endl;
	}	
	
	void acknowledge() override
	{
		std::cout << "Acknowledging data packet" << std::endl;
	}
};  


// Context delegates state-specific behavior to current state object.
class TCPConnection
{
private:
	// Maintains a reference to current state object
	TCPState* state;

public:
	TCPConnection(TCPState* initialState) : state(initialState) {}
	
	void setState(TCPState* newState)
	{
		state = newState;
	}	
	
	// Delegate the state specific behavior to the current state object and can transition into different state by changing the state reference.
	void open()
	{
		state->open();
		setState(new  TCPEstablishedState());
	}

	void close()
	{
		state->close();
		setState(new TCPClosedState());
	}

	void acknowledge()
	{
		state->acknowledge();
	}
};


// Client interact with the TCPConnection to open, close and acknowledge the connection.
 
int main()
{
	TCPState* initialState = new TCPClosedState();
	TCPConnection* connection = new  TCPConnection(initialState);

	connection->open();
	
	connection->acknowledge();

	connection->close();

	delete initialState;
	delete connection;

	return 0;
}

