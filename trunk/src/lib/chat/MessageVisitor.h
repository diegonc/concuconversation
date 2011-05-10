#ifndef MESSAGEVISITOR_H
#define MESSAGEVISITOR_H

class MessageVisitor;

#include <chat/JoinMessage.h>
#include <chat/QuitMessage.h>
#include <chat/TextMessage.h>

class MessageVisitor
{
	public:
		virtual void visit (const JoinMessage& msg) = 0;
		virtual void visit (const QuitMessage& msg) = 0;
		virtual void visit (const TextMessage& msg) = 0;
};

#endif
