/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEGTText.cpp
 * Author: demensdeum
 *
 * Created on March 26, 2017, 8:13 PM
 */

#include <FlameSteelEngineGameToolkit/Const/FSEGTConst.h>
#include "FSEGTText.h"

FSEGTText::FSEGTText(shared_ptr<string> text)
{

    auto identifier = make_shared<string>(FSEGTConstComponentsText.c_str());

    setClassIdentifier(identifier);
    setInstanceIdentifier(identifier);

    this->text = text;

}

FSEGTText::FSEGTText(const FSEGTText& )
{
}

FSEGTText::~FSEGTText()
{
}
