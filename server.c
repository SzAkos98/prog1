/***************************************/
/*              TCP server             */
/***************************************/
#include <string>
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <list>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024                      // buffer size
#define PORT_NO 2001                      // port number
#define error(a,b) fprintf(stderr, a, b)  // error 'function'

class Deck {
public:
  int id;
  std::string color;
  int card_val;
  std::string val;
// bool operator==(const int & id) const { return this->id == id;}
}  ;
 std::string colors []  = {"Káró","Treff","Kör","Pikk"};
 std::string vals[] = {"1","2","3","4","5","6","7","8","9","10","Jumbó","Dáma","Király","Ász"};



void make_deck (std::vector<Deck>& cards){
        int j = 0;
  for(int i=0; i < cards.size();i++){

       cards[i].id = i;

          if ((i%14)==0 && i >0)
            j++;
        cards[i].color = colors[j];
        cards[i].val = vals[i%14];

	if(  cards[i].val == "Ász")
              cards[i].card_val = 11;
              else if (cards[i].val == "1" )
              cards[i].card_val = 1;
              else if (cards[i].val == "2" )
              cards[i].card_val = 2;
              else if (cards[i].val == "3" )
              cards[i].card_val = 3;
              else if (cards[i].val == "4" )
              cards[i].card_val = 4;
              else if (cards[i].val == "5")
              cards[i].card_val = 5;
              else if (cards[i].val == "6")
              cards[i].card_val = 6;
              else if (cards[i].val == "7")
              cards[i].card_val = 7;
              else if (cards[i].val == "8")
              cards[i].card_val = 8;
              else if (cards[i].val == "9")
              cards[i].card_val = 9;
              else if (cards[i].val == "10")
              cards[i].card_val = 10;
              else if (cards[i].val == "Jumbó")
              cards[i].card_val = 10;
              else if (cards[i].val == "Dáma")
              cards[i].card_val = 10;
              else if (cards[i].val == "Király")
              cards[i].card_val = 10;

  }

}


int ran (int i){return std::rand()%i;}
std::vector<Deck> shuffle_deck(std::vector<Deck> cards){
std::random_shuffle ( cards.begin(), cards.end(), ran);
return cards;
}


/*void show_deck (std::vector<int> v, const std::vector<Deck> &cards){
for(int j=0;j<v.size();j++)
for(int i=0;i<sards.size();i++){
if(v[j] == cards[i].id){*/




int main(int argc, char *argv[] ){ 	// arg count, arg vector 

std::vector<Deck> deck (52);
make_deck(deck);





   /* Declarations */
   int fd;	        	           		// socket endpt
   int fdc;                        	// socket endpt
   int flags;                      	// rcv flags
   struct sockaddr_in server;      	// socket name (addr) of server
   struct sockaddr_in client;	     	// socket name of client
   int server_size;                	// length of the socket addr. server
   unsigned int client_size;                	// length of the socket addr. client
   int bytes;		           					// length of buffer 
   int rcvsize;                    	// received bytes
   int trnmsize;                   	// transmitted bytes
   int err;                        	// error code
   char on;                        	// 
   char buffer[BUFSIZE+1];	     		// datagram dat buffer area   
memset(&buffer, 0, sizeof buffer);
   /* Initialization */
   on                     = 1;
   flags                  = 0;
   bytes                  = BUFSIZE;
   server_size            = sizeof server;
   client_size            = sizeof client;
   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port        = htons(PORT_NO);

   /* Creating socket */
   fd = socket(AF_INET, SOCK_STREAM, 0 );
   if (fd < 0) {
      error("%s: Socket creation error\n",argv[0]);
      exit(1);
      }

   /* Setting socket options */
   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

   /* Binding socket */
   err = bind(fd, (struct sockaddr *) &server, server_size);
   if (err < 0) {
      error("%s: Cannot bind to the socket\n",argv[0]);
      exit(2);
      }

   /* Listening */
   err = listen(fd, 10);
   if (err < 0) {
      error("%s: Cannot listen to the socket\n",argv[0]);
      exit(3);
      }

printf("Waiting for Player\n");
   /* Accepting connection request */
   fdc = accept(fd, (struct sockaddr *) &client, &client_size);
   if (fdc < 0) {
      error("%s: Cannot accept on socket\n",argv[0]);
      exit(4);
      }
//------------------------------------------
printf("START\n");
//------------------------------------------
std::srand( unsigned(std::time(0)));
std::vector<Deck> shuffled_deck(shuffle_deck(deck));
std::list<Deck> dealer_deck;
std::copy(shuffled_deck.begin(),shuffled_deck.end(), back_inserter( dealer_deck));
int ID;
int ans;
int sumD=0;
int sumP=0;
int x =0;
if (x==0){

	   sprintf(buffer,"%d", dealer_deck.front().id);
	   //bytes = strlen(buffer) + 1;
	   trnmsize = send(fdc, buffer, sizeof buffer, flags);
	   if (trnmsize < 0) {
	      error("%s: Cannot send data to the client.\n",argv[0]);
	      exit(6);
	     } 
	ID=dealer_deck.front().id;
	sumP+=deck[ID].card_val;
	dealer_deck.pop_front();
	x++;

}


if (x==1){

	   sprintf(buffer,"%d", dealer_deck.front().id);
	   //bytes = strlen(buffer) + 1;
	   trnmsize = send(fdc, buffer, sizeof buffer, flags);
	   if (trnmsize < 0) {
	      error("%s: Cannot send data to the client.\n",argv[0]);
	      exit(6);
	     } 
	ID=dealer_deck.front().id;
	sumD+=deck[ID].card_val;
	dealer_deck.pop_front();
x++;
}


if (x==2){

	    sprintf(buffer,"%d", dealer_deck.front().id);
	   //bytes = strlen(buffer) + 1;
	   trnmsize = send(fdc, buffer, sizeof buffer, flags);
	   if (trnmsize < 0) {
	      error("%s: Cannot send data to the client.\n",argv[0]);
	      exit(6);
	     } 
	ID=dealer_deck.front().id;
	sumP+=deck[ID].card_val;
	dealer_deck.pop_front();
	x++;
}

if (x==3){

	   sprintf(buffer,"%d", dealer_deck.front().id);
	   //bytes = strlen(buffer) + 1;
	   trnmsize = send(fdc, buffer, sizeof buffer, flags);
	   if (trnmsize < 0) {
	      error("%s: Cannot send data to the client.\n",argv[0]);
	      exit(6);
	     } 
	ID=dealer_deck.front().id;
	sumD+=deck[ID].card_val;
	dealer_deck.pop_front();
	x++;
}

sprintf(buffer,"%d", sumP);

   //bytes = strlen(buffer) + 1;
   trnmsize = send(fdc, buffer, sizeof buffer, flags);
   if (trnmsize < 0) {
      error("%s: Cannot send data to the client.\n",argv[0]);
      exit(6);
     } 


//--------------------------------------------------
printf("Kezdő lapok kiosztva.\n");
//--------------------------------------------------
int z=1;
while(z=1){
	   rcvsize = recv( fdc, buffer, sizeof buffer, flags );
	   if (rcvsize < 0) {
	      error("%s: Cannot receive from the socket\n",argv[0]);
	      exit(5);
	      }



	sscanf(buffer, "%d", &ans);
	if(ans==1){

		   sprintf(buffer,"%d", dealer_deck.front().id);
		   //bytes = strlen(buffer) + 1;
		   trnmsize = send(fdc, buffer, sizeof buffer, flags);
		   if (trnmsize < 0) {
		      error("%s: Cannot send data to the client.\n",argv[0]);
		      exit(6);
		     } 
		ID=dealer_deck.front().id;
		sumP+=deck[ID].card_val;
		dealer_deck.pop_front();

		sprintf(buffer,"%d", sumP);
		   //bytes = strlen(buffer) + 1;
		   trnmsize = send(fdc, buffer, sizeof buffer, flags);
		   if (trnmsize < 0) {
		      error("%s: Cannot send data to the client.\n",argv[0]);
		      exit(6);
		     } 
	   rcvsize = recv( fdc, buffer, sizeof buffer, flags );
	   if (rcvsize < 0) {
	      error("%s: Cannot receive from the socket\n",argv[0]);
	      exit(5);
	      }



	sscanf(buffer, "%d", &ans);


	
	if(sumP>21){
		sprintf(buffer,"Vesztettél");
		   trnmsize = send(fdc, buffer, sizeof buffer, flags);
		   if (trnmsize < 0) {
		      error("%s: Cannot send data to the client.\n",argv[0]);
		      exit(6);
		     } 


	}
	   rcvsize = recv( fdc, buffer, sizeof buffer, flags );
	   if (rcvsize < 0) {
	      error("%s: Cannot receive from the socket\n",argv[0]);
	      exit(5);
	      }



	sscanf(buffer, "%d", &ans);
}

	 else if(ans==2){
		while( sumD<20 ){
			sprintf(buffer,"%d", dealer_deck.front().id);
			   //bytes = strlen(buffer) + 1;
			   trnmsize = send(fdc, buffer, sizeof buffer, flags);
			   if (trnmsize < 0) {
			      error("%s: Cannot send data to the client.\n",argv[0]);
			      exit(6);
			     } 
			ID=dealer_deck.front().id;
			sumD+=deck[ID].card_val;
			dealer_deck.pop_front();

			sprintf(buffer,"%d", sumD);
			   //bytes = strlen(buffer) + 1;
			   trnmsize = send(fdc, buffer, sizeof buffer, flags);
			   if (trnmsize < 0) {
			      error("%s: Cannot send data to the client.\n",argv[0]);
			      exit(6);
			     } 
	   rcvsize = recv( fdc, buffer, sizeof buffer, flags );
	   if (rcvsize < 0) {
	      error("%s: Cannot receive from the socket\n",argv[0]);
	      exit(5);
	      }



	sscanf(buffer, "%d", &ans);
			if(sumD<=21 && sumD>=20){
			sprintf(buffer,"%d", sumD);
			   //bytes = strlen(buffer) + 1;
			   trnmsize = send(fdc, buffer, sizeof buffer, flags);
			   if (trnmsize < 0) {
			      error("%s: Cannot send data to the client.\n",argv[0]);
			      exit(6);
			     } 
	   rcvsize = recv( fdc, buffer, sizeof buffer, flags );
	   if (rcvsize < 0) {
	      error("%s: Cannot receive from the socket\n",argv[0]);
	      exit(5);
	      }



	sscanf(buffer, "%d", &ans);

			}
			if(sumD>21){
						sprintf(buffer,"Nyertél");
		   trnmsize = send(fdc, buffer, sizeof buffer, flags);
		   if (trnmsize < 0) {
		      error("%s: Cannot send data to the client.\n",argv[0]);
		      exit(6);
		     } 
			}
		}
	}




	 else if(ans==3){
		   close (fdc);
		   close (fd);
		   exit(0);
		}




	else{
		sprintf(buffer,"Wrong input");
		   //bytes = strlen(buffer) + 1;
		   trnmsize = send(fdc, buffer, sizeof buffer, flags);
		   if (trnmsize < 0) {
		      error("%s: Cannot send data to the client.\n",argv[0]);
		      exit(6);
		     } 

	}
}


}

