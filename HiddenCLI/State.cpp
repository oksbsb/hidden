#include "State.h"
#include <iostream>

using namespace std;

CommandState::CommandState() : m_command(L"/state")
{
}

CommandState::~CommandState()
{
}

bool CommandState::CompareCommand(std::wstring& command)
{
	return (command == m_command);
}

void CommandState::LoadArgs(Arguments& args)
{
	wstring state, enable;

	if (!args.GetNext(state))
		throw WException(-2, L"Error, mismatched argument #1 for command 'state'");

	if (state == L"on")
		m_state = true;
	else if (state == L"off")
		m_state = false;
	else
		throw WException(-2, L"Error, mismatched argument #2 for command 'state'");
}

void CommandState::PerformCommand(Connection& connection)
{
	HidStatus status;

	status = Hid_SetState(connection.GetContext(), (m_state ? HidActiveState::StateEnabled : HidActiveState::StateDisabled));
	if (!HID_STATUS_SUCCESSFUL(status))
		throw WException(HID_STATUS_CODE(status), L"Error, command 'state' rejected");

	wcerr << L"Command 'state' successful" << endl;
	wcout << L"status:ok" << endl;
}
