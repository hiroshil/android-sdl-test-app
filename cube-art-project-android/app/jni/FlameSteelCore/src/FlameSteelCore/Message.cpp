/*
 * Message.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: demensdeum
 */

#include "Message.h"

Message::Message(shared_ptr<string> title, shared_ptr<string> text) {

    this->title = title;
    this->text = text;

}

shared_ptr<string> Message::getTitle() {

    return this->title;
}

shared_ptr<string> Message::getText() {

    return this->text;
}

Message::~Message() {
    // TODO Auto-generated destructor stub
}
