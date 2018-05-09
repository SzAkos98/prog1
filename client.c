/***************************************/
/*             TCP client              */
/***************************************/
#include <string>
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define BUFSIZE 1024
#define PORT_NO 2001
#define error(a,b) fprintf(stderr, a, b)

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



int main(int argc, char *argv[] ) {// arg count, arg vector   


std::vector<Deck> deck (52);
make_deck(deck);



   /* Declarations */
   int fd;	                       // socket endpt	
   int flags;                      // rcv flags
   struct sockaddr_in server;	     // socket name (addr) of server 
   struct sockaddr_in client;	     // socket name of client 
   int server_size;                // length of the socket addr. server 
   int client_size;                // length of the socket addr. client 
   int bytes;    	                 // length of buffer 
   int rcvsize;                    // received bytes
   int trnmsize;                   // transmitted bytes
   int err;                        // error code
   int ip;							 // ip address
   char on;                        // 
   char buffer[BUFSIZE+1];         // datagram dat buffer area
   char server_addr[16];           // server address	
memset(&buffer, 0, sizeof buffer); 

  /* Initialization */
   on    = 1;
   flags = 0;
   server_size = sizeof server;
   client_size = sizeof client;
   sprintf(server_addr, "%s", argv[1]);
   ip = inet_addr(server_addr);
   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = ip;
   server.sin_port        = htons(PORT_NO);

/* Creating socket */
   fd = socket(AF_INET, SOCK_STREAM, 0);
   if (fd < 0) {
      error("%s: Socket creation error.\n",argv[0]);
      exit(1);
   }

   /* Setting socket options */
   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

   /* Connecting to the server */
   err = connect(fd, (struct sockaddr *) &server, server_size);
   if (err < 0) {
      error("%s: Cannot connect to the server.\n", argv[0]);
      exit(2);
   }
int sumP;
printf("START\n");
printf("1.Lapot kérek        2.Megállok       3.Kilépek\n");

 printf("A lapjaid:\n");
int x=0;
std::vector<int> dealer_card(2);
int card_id;
if(x==0){
	  // bytes = strlen(buffer)+1;
	   rcvsize = recv( fd, buffer, sizeof buffer, flags );
	   if (rcvsize < 0) {
	      error("%s: Cannot receive data from the socket.\n", argv[0]);
	      exit(4);

	   }
	x++;
	 sscanf(buffer, "%d", &card_id);
	 std::cout<<deck[card_id].val<<" ";
	 std::cout<<deck[card_id].color<<" ";

}

if(x==1){
	   rcvsize = recv( fd, buffer, sizeof buffer, flags );
	   if (rcvsize < 0) {
	      error("%s: Cannot receive data from the socket.\n", argv[0]);
	      exit(4);

	   }
	x++;
	sscanf(buffer, "%d", &card_id);
	dealer_card.push_back(card_id);
	 //printf("%d , ",card_id);

}

if(x==2){
	   rcvsize = recv( fd, buffer, sizeof buffer, flags );
	   if (rcvsize < 0) {
	      error("%s: Cannot receive data from the socket.\n", argv[0]);
	      exit(4);

	   }
	x++;
	sscanf(buffer, "%d", &card_id);
	 std::cout<<deck[card_id].val<<" ";
	 std::cout<<deck[card_id].color<<" "<<std::endl;

}

if(x==3){
	   rcvsize = recv( fd, buffer, sizeof buffer, flags );
	   if (rcvsize < 0) {
	      error("%s: Cannot receive data from the socket.\n", argv[0]);
	      exit(4);

	   }
	x++;
	printf("Az osztó 2. lapja: ");
	 std::cout<<deck[card_id].val<<" ";
	 std::cout<<deck[card_id].color<<" "<<std::endl;


}


   rcvsize = recv( fd, buffer, sizeof buffer, flags );
   if (rcvsize < 0) {
      error("%s: Cannot receive data from the socket.\n", argv[0]);
      exit(4);
   }

sscanf(buffer, "%d", &sumP);
printf("Pontszám: %d \n",sumP);


//-------------------------------------------------------
int ans;
int ID;
int z=1;
	while(z=1){

		scanf("%d", &ans);

		sprintf(buffer, "%d", ans);
		   trnmsize = send(fd, buffer, sizeof buffer, flags);
		   if (trnmsize < 0) {
		      error("%s: Cannot send data to server.\n", argv[0]);
		      exit(3);
		  }

		if(sumP<=20 && ans==1){

			printf("Új lap:\n");

			   rcvsize = recv( fd, buffer, sizeof buffer, flags );
			   if (rcvsize < 0) {
			      error("%s: Cannot receive data from the socket.\n", argv[0]);
			      exit(4);

			   }
			sscanf(buffer, "%d", &card_id);
			   rcvsize = recv( fd, buffer, sizeof buffer, flags );
			   if (rcvsize < 0) {
			      error("%s: Cannot receive data from the socket.\n", argv[0]);
			      exit(4);

			   }
			sscanf(buffer, "%d", &sumP);
				 std::cout<<deck[card_id].val<<" ";
				 std::cout<<deck[card_id].color<<" "<<std::endl;
			printf("Pontszám: %d \n",sumP);
		scanf("%d", &ans);

		sprintf(buffer, "%d", ans);
		   trnmsize = send(fd, buffer, sizeof buffer, flags);
		   if (trnmsize < 0) {
		      error("%s: Cannot send data to server.\n", argv[0]);
		      exit(3);
		  }

			}
		 if(sumP>21){
			   rcvsize = recv( fd, buffer, sizeof buffer, flags );
			   if (rcvsize < 0) {
			      error("%s: Cannot receive data from the socket.\n", argv[0]);
			      exit(4);

			   }
			printf("%s\n",buffer);
		scanf("%d", &ans);

		sprintf(buffer, "%d", ans);
		   trnmsize = send(fd, buffer, sizeof buffer, flags);
		   if (trnmsize < 0) {
		      error("%s: Cannot send data to server.\n", argv[0]);
		      exit(3);
		  }
		}

		int sumD;
		 if(ans==2){

			while( sumD<20){
			   rcvsize = recv( fd, buffer, sizeof buffer, flags );
			   if (rcvsize < 0) {
			      error("%s: Cannot receive data from the socket.\n", argv[0]);
			      exit(4);

			   }

			sscanf(buffer, "%d", &card_id);
			//dealer_card.push_back(card_id);

			   rcvsize = recv( fd, buffer, sizeof buffer, flags );
			   if (rcvsize < 0) {
			      error("%s: Cannot receive data from the socket.\n", argv[0]);
			      exit(4);

			   }
				for(int i=0; i<dealer_card.size();i++){
					std::cout<<deck[dealer_card[i]].val<<" ";
					std::cout<<deck[dealer_card[i]].color<<" ";
				}
				 std::cout<<deck[card_id].val<<" ";
				 std::cout<<deck[card_id].color<<" "<<std::endl;
				printf("Osztó pontszáma: %s \n", buffer);
		scanf("%d", &ans);

		sprintf(buffer, "%d", ans);
		   trnmsize = send(fd, buffer, sizeof buffer, flags);
		   if (trnmsize < 0) {
		      error("%s: Cannot send data to server.\n", argv[0]);
		      exit(3);
		  }

			}


			sscanf(buffer, "%d", &sumD);
			 if(sumD<=21){
				   rcvsize = recv( fd, buffer, sizeof buffer, flags );
				   if (rcvsize < 0) {
				      error("%s: Cannot receive data from the socket.\n", argv[0]);
				      exit(4);

				   }
			}
			if(sumP<sumD){
				printf("Vesztettél\n");
		   close (fd);
		   exit(0);
			}
			if(sumP>sumD){
				printf("Nyertél\n");
		   close (fd);
		   exit(0);
			}
			if(sumP==sumD){
				printf("Döntetlen\n");
		   close (fd);
		   exit(0);
			}
			

			
			
			else if(sumD>21){
				   rcvsize = recv( fd, buffer, sizeof buffer, flags );
				   if (rcvsize < 0) {
				      error("%s: Cannot receive data from the socket.\n", argv[0]);
				      exit(4);

				   }
				printf("Graturálok nyertél.\n");
		   close (fd);
		   exit(0);
			}

		}
		if(ans==3){
		   close (fd);
		   exit(0);
		}
		else{
		   rcvsize = recv( fd, buffer, sizeof buffer, flags );
		    if (rcvsize < 0) {
		      error("%s: Cannot receive data from the socket.\n", argv[0]);
		      exit(4);
			   }
		   printf("%s \n",buffer);
		   close (fd);
		   exit(0);
		}
	}


} 
