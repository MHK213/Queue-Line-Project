#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include "clsDate.h"

using namespace std;

class clsQueueLine
{
private:

	string _Prefix = "";
	int _AvergeServeTime = 0;
	int _TotalTickets = 0;

	class clsTicket {
	private:
		int _Number = 0;
		string _Prefix = "";
		string _TicketTime = "";
		int _WaitingClients = 0;
		int _AvergeServeTime = 0;
		int _ExpectedServeTime = 0;

	public:

		clsTicket(string Prefix, int TotalTickets, int WaitingClients, int AvergeServeTime) {
			_Number = TotalTickets;
			_Prefix = Prefix;
			_TicketTime = clsDate::GetSystemDateTimeString();
			_WaitingClients = WaitingClients;
			_AvergeServeTime = AvergeServeTime;
		}

		string Prefix() {
			return _Prefix;
		}

		int Number() {
			return _Number;
		}

		string FullNumber() {
			return _Prefix + to_string(_Number);
		}

		string TicketTime() {
			return _TicketTime;
		}

		int WaitingClients() {
			return _WaitingClients;
		}

		int ExpectedServeTime() {
			return _AvergeServeTime * _WaitingClients;
		}

		void Print() {
			cout << "\n\t\t\t  _______________________\n";
			cout << "\n\t\t\t\t    " << FullNumber();
			cout << "\n\n\t\t\t    " << _TicketTime;
			cout << "\n\t\t\t    Wating Clients = " << _WaitingClients;
			cout << "\n\t\t\t      Serve Time In";
			cout << "\n\t\t\t       " << ExpectedServeTime() << " Minutes.";
			cout << "\n\t\t\t  _______________________\n";
		}
	};

public:

	queue <clsTicket> LineQueue;

	clsQueueLine(string Prefix, int AvergeServeTime) {
		_Prefix = Prefix;
		_AvergeServeTime = AvergeServeTime;
		_TotalTickets = 0;
	}

	void IssueTicket() {

		_TotalTickets++;
		clsTicket Ticket(_Prefix, _TotalTickets, WaitingClients(), _AvergeServeTime);
		LineQueue.push(Ticket);
	}

	int WaitingClients() {
		return LineQueue.size();
	}

	string WhoIsNext() {
		if (LineQueue.empty())
			return "\nNo Clients Left\n";
		else
			return LineQueue.front().FullNumber();
	}

	bool ServeNextClient() {
		if (LineQueue.empty())
			return false;

		LineQueue.pop();
		return true;
	}

	int ServedClients() {
		return _TotalTickets - WaitingClients();
	}

	void PrintInfo() {
		cout << "\n\t\t\t ________________________________\n";
		cout << "\n\t\t\t\tQueue Info";
		cout << "\n\t\t\t ________________________________\n";
		cout << "\n\t\t\t   Prefix          = " << _Prefix;
		cout << "\n\t\t\t   Total Tickets   = " << _TotalTickets;
		cout << "\n\t\t\t   Served Clients  = " << ServedClients();
		cout << "\n\t\t\t   Waiting Clients = " << WaitingClients();
		cout << "\n\t\t\t ________________________________\n\n";
	}

	void PrintTicketsLineRTL() {

		if (LineQueue.empty())
			cout << "\n\t\tTickets: No Tickets.";
		else
			cout << "\n\t\tTickets: ";

		queue <clsTicket> TempQueueLine = LineQueue;

		while (!TempQueueLine.empty()) {
			clsTicket Ticket = TempQueueLine.front();
			cout << " " << Ticket.FullNumber() << " <-- ";
			TempQueueLine.pop();
		}
		cout << endl;
	}

	void PrintTicketsLineLTR() {

		if (LineQueue.empty())
			cout << "\n\t\tTickets: No Tickets.";
		else
			cout << "\n\t\tTickets: ";

		queue <clsTicket> TempQueue = LineQueue;
		stack <clsTicket> TempStack1;

		while (!TempQueue.empty()) {
			TempStack1.push(TempQueue.front());
			TempQueue.pop();
		}

		while (!TempStack1.empty()) {
			clsTicket Ticket = TempStack1.top();
			cout << " " << Ticket.FullNumber() << " <-- ";
			TempStack1.pop();
		}
		cout << endl;
	}

	void PrintAllTickets() {

		if (LineQueue.empty()) {
			cout << "\n\n\t\t\t     ---Tickets---";
			return;
		}

		cout << "\n\n\t\t\t     ---Tickets---";

		queue <clsTicket> TempQueue1 = LineQueue;

		while (!TempQueue1.empty()) {
			TempQueue1.front().Print();
			TempQueue1.pop();
		}
	}
};