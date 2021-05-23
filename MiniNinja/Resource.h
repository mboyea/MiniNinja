#ifndef RESOURCE_H
#define RESOURCE_H
#pragma once

#include <iostream>

class Resource {
private:
protected:
public:
	// Generate serialized text data for this resource into the stream
	virtual std::ostream& Serialize(std::ostream& os);
	// Populate this resource by deserializing text data from the stream
	virtual std::istream& Deserialize(std::istream& is);
};

class ResourceModule : public Resource {

};

class ResourceTexture : public Resource {

};

class ResourceAnimation : public Resource {

};

class ResourceFont : public Resource {

};

#endif // !RESOURCE_H