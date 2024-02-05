#ifndef CANSMARTYCOFFRE_HPP
#define CANSMARTYCOFFRE_HPP

#include "mbed.h"
#include <cstdio>
#include "rtos.h"

/**
 * @file CANSmartyCoffre.hpp
 * @brief Fichier d'en-tête de la classe CANSmartyCoffre.
 */

/**
 * @class CANSmartyCoffre
 * @brief Classe pour gérer la communication CAN pour le coffre.
 *
 * Cette classe fournit des méthodes pour envoyer des signaux de détection et de désarmement, ainsi que pour démarrer et arrêter le pinging.
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
     * @brief Envoie un signal de détection.
     */
    void SendDetectionSignal();

    /**
     * @brief Envoie un signal de désarmement.
     */
    void SendDisarmedSignal();

    /**
     * @brief Commence à écouter les messages CAN.
     */
    void StartListener();

private:
    /**
     * @brief Envoie un message CAN.
     * @param msg Le message CAN à envoyer.
     * @return true si le message a été envoyé avec succès, false sinon.
     */
    bool SendCanMessage(CANMessage msg);

    CAN& commCan; ///< Référence à l'objet CAN utilisé pour la communication.
    Thread thread; ///< Thread utilisé pour la queue d'événements.
    EventQueue queue; ///< Queue d'événements pour les pings périodiques.
    int eventID; ///< ID de l'événement de pinging périodique.
    int id_noeud; ///< Identifiant du noeud.
};

#endif //CANSMARTYCOFFRE_HPP

/* UML
- commCan: CAN&
- thread: Thread
- queue: EventQueue
- eventID: int
- id_noeud: int

+ CANSmartyCoffre(CAN&, int)
+ ~CANSmartyCoffre()
+ StartPinging(): void
+ StopPinging(): void
+ SendDetectionSignal(): void
+ SendDisarmedSignal(): void
+ StartListener(): void
- SendCanMessage(CANMessage): bool
*/