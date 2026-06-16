#pragma once
#include "Global.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsTransferLogScreen : protected clsScreen
{
private:
    static void _PrintTransfersLogList(const size_t& ListNumbers) {
        cout << "________________________________________________________________________________________________________________________" << endl;
        cout << "\n\t\t\t\t\t\t Users Transfer Log List:\n \t\t\t\t\t\t There are " << ListNumbers << " Transfer(s).\t\t\t\t\t" << endl;
        cout << "________________________________________________________________________________________________________________________" << endl << endl;
    }
    static void _PrintTransfersTableDecoration() {
        cout << left << setw(25) << "Date/Time" << "| ";
        cout << left << setw(20) << "From User" << "| ";
        cout << left << setw(20) << "To User" << "| ";
        cout << left << setw(12) << "Amount" << endl;
        cout << "________________________________________________________________________________________________________________________";
    }
    static void _PrintTransfersInTheList(const clsBankClient::stTransferLogRecord & Record) {
        cout << endl;
        cout << left << setw(25) << Record.DateTime << "| ";
        cout << left << setw(20) << Record.SourceAccountNumber << "| ";
        cout << left << setw(20) << Record.DestinationAccountNumber << "| ";
        cout << left << setw(12) << Record.TransferAmount << endl;
        cout << left << setw(12) << Record.SourceAccountBalanceAfterTransfer << "| ";
        cout << left << setw(12) << Record.DestinationAccountBalanceAfterTransfer << "| ";
        cout << left << setw(12) << Record.UserName;
    }
    static void _ShowTransfersLog(const vector<clsBankClient::stTransferLogRecord>& vTransfers) {
        _PrintTransfersLogList(vTransfers.size());
        _PrintTransfersTableDecoration();

        if (vTransfers.size() == 0) {
            cout << "\n\t\t\t\tNo Transfers Available In the System!\n";
        }
        else {
            for (const clsBankClient::stTransferLogRecord& Record : vTransfers) {
                _PrintTransfersInTheList(Record);
            }
            cout << endl;
        }
        cout << "________________________________________________________________________________________________________________________" << endl;
    }
public: 
    static void Show() {
        if (!CheckAccessRights(clsUser::pTranactions))
            return;
        ClearScreen();
		ShowScreen("Transfer Log Screen");
		_ShowTransfersLog(clsBankClient::GetTransfersLogList());
		Pause();
    }
};

