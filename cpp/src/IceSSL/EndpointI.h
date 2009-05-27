// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_SSL_ENDPOINT_I_H
#define ICE_SSL_ENDPOINT_I_H

#include <Ice/EndpointI.h>
#include <Ice/EndpointFactory.h>
#include <IceSSL/Endpoint.h>
#include <IceSSL/InstanceF.h>

namespace IceSSL
{

const Ice::Short EndpointType = 2;

class EndpointI : public IceInternal::EndpointI, public SslEndpoint
{
public:

    EndpointI(const InstancePtr&, const std::string&, Ice::Int, Ice::Int, const std::string&, bool);
    EndpointI(const InstancePtr&, const std::string&, bool);
    EndpointI(const InstancePtr&, IceInternal::BasicStream*);

    // From SslEndpoint
    virtual std::string toString() const;
    virtual Ice::Int timeout() const;
    virtual bool compress() const;
    virtual bool datagram() const;
    virtual bool secure() const;
    virtual std::string host() const;
    virtual Ice::Int port() const;

    // From IceInternal::EndpointI
    virtual void streamWrite(IceInternal::BasicStream*) const;
    virtual Ice::Short type() const;
    virtual IceInternal::EndpointIPtr timeout(Ice::Int) const;
    virtual IceInternal::EndpointIPtr connectionId(const ::std::string&) const;
    virtual IceInternal::EndpointIPtr compress(bool) const;
    virtual IceInternal::TransceiverPtr transceiver(IceInternal::EndpointIPtr&) const;
    virtual std::vector<IceInternal::ConnectorPtr> connectors() const;
    virtual void connectors_async(const IceInternal::EndpointI_connectorsPtr&) const;
    virtual IceInternal::AcceptorPtr acceptor(IceInternal::EndpointIPtr&, const std::string&) const;
    virtual std::vector<IceInternal::EndpointIPtr> expand() const;
    virtual bool equivalent(const IceInternal::EndpointIPtr&) const;

    virtual bool operator==(const IceInternal::EndpointI&) const;
    virtual bool operator!=(const IceInternal::EndpointI&) const;
    virtual bool operator<(const IceInternal::EndpointI&) const;

private:

    virtual std::vector<IceInternal::ConnectorPtr> connectors(const std::vector<struct sockaddr_storage>&) const;
    
#if defined(__SUNPRO_CC)
    //
    // COMPILERFIX: prevent the compiler from emitting a warning about
    // hidding these operators.
    //
    using LocalObject::operator==;
    using LocalObject::operator<;
#endif

    //
    // All members are const, because endpoints are immutable.
    //
    const InstancePtr _instance;
    const std::string _host;
    const Ice::Int _port;
    const Ice::Int _timeout;
    const std::string _connectionId;
    const bool _compress;
};

class EndpointFactoryI : public IceInternal::EndpointFactory
{
public:

    virtual ~EndpointFactoryI();

    virtual Ice::Short type() const;
    virtual std::string protocol() const;
    virtual IceInternal::EndpointIPtr create(const std::string&, bool) const;
    virtual IceInternal::EndpointIPtr read(IceInternal::BasicStream*) const;
    virtual void destroy();

private:

    EndpointFactoryI(const InstancePtr&);
    friend class Instance;

    InstancePtr _instance;
};

}

#endif
