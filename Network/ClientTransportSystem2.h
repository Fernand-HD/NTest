#pragma once

#include "ClientTransportSystemIntf.h"
#include "AddressTranslator.h"
#include "Network.h"
#include "Address.h"
#include "LoginClient.h"
#include "Transport.h"
#include "transport/TLProtocolHandlerFactory.h"

namespace Transport
{

  class ClientTransportSystem2 : public IClientTransportSystem, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( ClientTransportSystem2, IClientTransportSystem, BaseObjectMT );
  public:
    ClientTransportSystem2::ClientTransportSystem2(Network::INetworkDriver* _pNetDriver, 
      Transport::MessageFactory* _pFactory, 
      Login::ClientVersion const & version);
    ClientTransportSystem2( Network::INetworkDriver* _pNetDriver, Transport::MessageFactory* _pFactory, 
      Login::ClientVersion const & version,
      StrongMT<Transport::ITransportSystem> const & pts);
    virtual ~ClientTransportSystem2();

    // IClientTransportSystem
    void Login( const Network::NetAddress& loginServerAddress, const string& login, const string& _password, 
      const string& sessionKey="", Login::LoginType::Enum _loginType = Login::LoginType::ORDINARY);
    void Logout();
    EStatus::Enum GetStatus();

    Login::ELoginResult::Enum GetLoginResult() const;
    int GetUserId() const { return userId; }
    int GetListenPort() const { return clientsListenPort; }
    const string& GetUserLogin() const { return login; } 
    Network::INetworkDriver *GetNetworkDriver() const { return netDriver; }

    StrongMT<Transport::IChannel> OpenChannel( Transport::TServiceId interfaceId,
      unsigned int pingperiod = Defaults::GetPingPeriod(), unsigned int to = Defaults::GetOpenChannelTimeout());

    Transport::TServiceId GetSessionPath() const { return sessionPath; };

    Network::NetAddress GetRelayAddress() const { return relayAddress; }
    Network::NetAddress GetSecondaryRelayAddress() const { return secondaryRelayAddress; };

    void Step();

  private:
    enum State
    {
      NotInitialized,
      LoggingIn,
      ContactingRelay,
      Working,
      Disconnected,
      Failed,
    };

    ClientTransportSystem2::State state;

    Network::INetworkDriver *netDriver;
    Transport::MessageFactory* factory;

    StrongMT<Login::LoginClient> loginClient;
    Login::ELoginResult::Enum loginResult;
    Network::NetAddress loginServerAddress;
    int userId;
    string login;
    string sessionId;
    Network::NetAddress relayAddress;
    Network::NetAddress secondaryRelayAddress;
    Transport::TServiceId sessionPath;
    int clientsListenPort;

    StrongMT<Transport::ITransportSystem> transport_;
    StrongMT<Transport::IChannel> relayChannel;
    StrongMT<Transport::IChannel> secondaryRelayChannel;

    wstring debugInfo;
    Transport::TChannels mandatoryChannels;

    void SetupTransport();
    bool Work();

    ClientTransportSystem2()
    {
    }
  };
}
