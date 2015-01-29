#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define MATH_PI (3.14159265359)

using namespace std;

void wait(){
    cin.ignore();
}

const int WIDHT = 600;
const int HEIGHT = 400;

int main()
{
	
	//create dynamic body


    // create the window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDHT,HEIGHT), "My window", sf::Style::Default, settings);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	//window.setVerticalSyncEnabled(true);

	// create font
	sf::Font font;
	font.loadFromFile("arial.ttf");

	// create text
	sf::Text text;
	text.setFont(font);
	
	sf::CircleShape shape(20);

	// define fps components
	sf::Clock clock;
	float fps = 1;
	char data[100];
	
	char mode = 'h';
	//create TCP socket
	sf::TcpSocket  socket;
	if (mode == 'h'){
		std::cout << "HOST MODE" << std::endl;
		std::cout << "Creating socket" << std::endl;
		sf::IpAddress ip("109.182.164.38");
		sf::Socket::Status status = socket.connect(ip, 53000);
		if (status != sf::Socket::Done){
			std::cout << "Cannot create socket to ip: " << ip << std::endl;
			return 1;
		} else 
			std::cout << "Socket was created" << std::endl;
	}
	if (mode == 'l'){
		std::cout << "CLIENTE MODE" << std::endl;
		sf::TcpListener listener;
		// bind the listener to a port
		if (listener.listen(53000) != sf::Socket::Done){
			std::cout << "Cannot find anythign on this port" << std::endl;
		} else {
			std::cout << "Listener was created" << std::endl;
		}
		std::cout << "Waiting for host" << std::endl;
		std::cout << "Listening.." << std::endl; 
		// accept a new connection
		if (listener.accept(socket) != sf::Socket::Done)
		{
			std::cout << "Cannot connect" << std::endl;
		} else
			std::cout << "Connected" << std::endl;
	}
	int x = 0; int y = 0;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
			if (mode == 'h'){
				if (event.type == sf::Event::MouseMoved){
					x = event.mouseMove.x;
					y = event.mouseMove.y;
				}
			}
		}
		
		
		// wasd key events
 		if (mode == 'h'){
			std::ostringstream msg;
			msg << x << "-" << y << "-";
			cout << msg.str() << endl;
			if (socket.send(msg.str().c_str(), 100) != sf::Socket::Done){
				std::cout << "Cannot send data | Error " << sf::Socket::Error << std::endl;
			}
		}
		if (mode == 'l'){
			std::size_t received;
			if (socket.receive(data, 100, received) != sf::Socket::Done){
				std::cout << "Error with reciving data | Error " << sf::Socket::Error << std::endl;
			} else {
				std::cout << "Data: " << data << std::endl;                
				int n=0;
                int c=0;
                for(int i=c; data[i] != 45; i++){
                    n *= 10;
                    n += (int)data[i]-48;
                    c = i+2;
                }
                x = n;
                n = 0;
                for(int i=c; data[i] != 45; i++){
                    n *= 10;
                    n += (int)data[i]-48;
                    c = i+2;
                }
				y = n;
				std::cout << x << " " << y << std::endl;
			}
			// start loop
		}

		// clear window

        window.clear(sf::Color::Black);
		shape.setPosition(x-20,y-20);
		window.draw(shape);
		

		// do game stuff
		
		// end the current frame
		float currentTime = clock.restart().asSeconds();
		fps = 1.f / currentTime;
		// display fps
		std::ostringstream s;
		s << (int)fps;
		text.setString(s.str());
		text.setCharacterSize(10);
		text.setColor(sf::Color::White);
		text.setPosition(10,10);
		window.draw(text);


		// draw stuff on window
        window.display();
    }
    window.close();
    return 0;
}
