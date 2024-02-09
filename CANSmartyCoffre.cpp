/**
 * @file CANSmartyCoffre.cpp
 * @brief Fichier source de la classe CANSmartyCoffre.
 */

#include "CANSmartyCoffre.hpp"


/**
 * @fn CANSmartyCoffre::CANSmartyCoffre(CAN& can1, int id_noeud)
 * @brief Constructeur de la classe CANSmartyCoffre.
 * @param can1 Référence à l'objet CAN utilisé pour la communication.
 * @param id_noeud Identifiant du noeud.
 */
CANSmartyCoffre::CANSmartyCoffre(CAN& can1, int id_noeud) : commCan(can1) {
    this->id_noeud = id_noeud;

    // Lance le thread d'émission avec la queue d'événements
    thread.start(callback(&queue, &EventQueue::dispatch_forever));

    // Demarre la reception sur interruption
    //commCan.attach(callback(this, &CANSmartyCoffre::ReceiveCanMessage), CAN::RxIrq);
}

/**
 * @fn CANSmartyCoffre::~CANSmartyCoffre()
 * @brief Destructeur de la classe CANSmartyCoffre.
 */
CANSmartyCoffre::~CANSmartyCoffre() {
    // Interrompt la queue d'événements, ce qui arrête aussi le thread
    queue.break_dispatch();

    thread.join();
}

/**
 * @fn bool CANSmartyCoffre::SendCanMessage(CANMessage msg)
 * @brief Envoie un message CAN.
 * @param msg Le message CAN à envoyer.
 * @return true si le message a été envoyé avec succès, false sinon.
 */
bool CANSmartyCoffre::SendCanMessage(CANMessage msg){
    if (commCan.write(msg)) {
        return true;
    } else {
        return false;
    }
}

/**
 * @fn void CANSmartyCoffre::StartPinging()
 * @brief Commence à envoyer des pings périodiques.
 */
void CANSmartyCoffre::StartPinging() {
    // Construction du message (trame)
    CANMessage msg;
        msg.id = id_noeud;
        msg.len = 1;
        msg.data[0] = id_noeud;
        msg.format = CANStandard;
        msg.type = CANData;

    // fonction lambda  utilisée pour capturer msg et le passer à SendPing.
    // La lambda est ensuite passée à call_every comme fonction periodique.
    eventID = queue.call_every(1000, [this, msg]() { this->SendCanMessage(msg); });
}

/**
 * @fn void CANSmartyCoffre::StopPinging()
 * @brief Arrête d'envoyer des pings périodiques.
 */
void CANSmartyCoffre::StopPinging() {
    // Interrompt le pinging periodique
    queue.cancel(eventID);
}

/**
 * @fn void CANSmartyCoffre::SendDetectionSignal()
 * @brief Envoie un signal de détection.
 */
void CANSmartyCoffre::SendDetectionSignal() {
    // Forme le message CAN
    CANMessage msg;
        msg.id = id_noeud+10;
        msg.len = 1;
        msg.data[0] = 0x01;
        msg.format = CANStandard;
        msg.type = CANData;

    // Demande l'emission du message
    queue.call([this, msg]() { this->SendCanMessage(msg); });
}

/**
 * @fn void CANSmartyCoffre::SendDisarmedSignal()
 * @brief Envoie un signal de désarmement.
 */
void CANSmartyCoffre::SendDisarmedSignal() {
    // Forme le message CAN
    CANMessage msg;
        msg.id = id_noeud+10;
        msg.len = 1;
        msg.data[0] = 0xFF;
        msg.format = CANStandard;
        msg.type = CANData;

    // Demande l'emission du message
    queue.call([this, msg]() { this->SendCanMessage(msg); });
}


    



