/**
 * @file CANSmartyCoffre.hpp
 * @brief Fichier d'en-tête de la classe CANSmartyCoffre.
 */

#ifndef CANSMARTYCOFFRE_HPP
#define CANSMARTYCOFFRE_HPP

#include "mbed.h"
#include <cstdio>
#include "rtos.h"


/**
 * @class CANSmartyCoffree
 * @brief Classe pour gérer la communication CAN pour le coffre.
 *
 * Cette classe fournit des méthodes pour envoyer des signaux de détection et de désarmement, ainsi que pour démarrer et arrêter le pinging.
 * Elle a pour avantage d'utiliser une queue d'événements pour les messages, ce qui permet de ne pas bloquer le programme principal.
 * Le formattage des messages CAN est fait dans cette classe, de cette manière le protocole applicatif est sur d'être respecté.
 * 
 * @see CAN
 * @see CANMessage
 * @see Thread
 * @see EventQueue
 * @see RTOS
 */

class CANSmartyCoffre {
public:
    /**
     * @brief Constructeur de la classe CANSmartyCoffre.
     * @param can1 Référence à l'objet CAN utilisé pour la communication.
     * @param id_noeud Identifiant du noeud.
     */
    CANSmartyCoffre(CAN& can1, int id_noeud);

    /**
     * @brief Destructeur de la classe CANSmartyCoffre.
     */
    ~CANSmartyCoffre();

    /**
     * @brief Commence à envoyer des pings périodiques.
     */
    void StartPinging();

    /**
     * @brief Arrête d'envoyer des pings périodiques.
     */
    void StopPinging();

    /**
     * @brief Envoie un signal comme quoi une intrusion à été détectée.
     */
    void SendDetectionSignal();

    /**
     * @brief Envoie un signal de désarmement.
     */
    void SendDisarmedSignal();

    /**
     * @brief Commence à écouter les messages CAN. Non fonctionnel pour l'instant.
     */
    void StartListener();

private:
    /**
     * @brief Envoie un message CAN.
     * @param msg Le message CAN à envoyer, de type CANMessage.
     * @return true si le message a été envoyé avec succès, false sinon.
     */
    bool SendCanMessage(CANMessage msg);

    CAN& commCan; ///< Référence à l'objet CAN utilisé pour la communication.
    Thread thread; ///< Thread utilisé pour la queue d'événements.
    EventQueue queue; ///< Queue d'événements pour les pings périodiques ou les messages occasionnels.
    int eventID; ///< ID de l'événement de pinging périodique.
    int id_noeud; ///< Identifiant du noeud.
};

#endif //CANSMARTYCOFFRE_HPP