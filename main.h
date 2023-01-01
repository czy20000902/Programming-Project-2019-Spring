#include<stdbool.h>
#include<math.h>
#include<windows.h>
#define MaxPerson 1024
#define FINE 50
#define PROFIT 10
#define MAXTIME 30
#define DEADLINE 3
#define PRICE 300
#define MAX 100
#define INF 50

struct Order
{
	int customer[2];
	int	restaurant[2];
	int serial;
	int timing;
	int Expectedtime;
	int delivering;
	int fine;
	struct Order * Next;
};
typedef struct Order order;

void Input();
void Output();
void hire();
void Send();
void warning();
void distribute();
void Anime();
void GetToLocation(int index);
