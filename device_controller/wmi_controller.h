/// \file wmi_controller.h
/// \brief контроллер, позволяющий работать с wmi

#pragma once
#ifndef DEVICE_CONTROLLER_WMI_CONTROLLER_H
#define DEVICE_CONTROLLER_WMI_CONTROLLER_H

#include <Wbemidl.h>
#include <memory>
#include <string>
#include <vector>
#include <memory>

namespace deviceController
{

class WmiController
{
public:
    /// \brief конструктор
    WmiController();

    /// \brief деструктор
    ~WmiController();

    /// \brief запрос одного параметра из класса через wmi
    /// \param wmiNamespace неймспейс в котором расположен объект данных
    /// \param wmiClass класс из которого будут запрошены данные
    /// \param objectField поле объекта, значение которого будет запрошено
    std::shared_ptr<std::vector<std::string>> Request(const std::string& wmiNamespace,
        const std::string& wmiClass, const std::string& objectField);

    /// \brief перегрузка метода для запроса нескольких полей данных из одного объекта
    /// \param wmiNamespace неймспейс в котором расположен объект данных
    /// \param wmiClass класс из которого будут запрошены данные
    /// \param objectFields вектор запрашиваемых полей данных
    std::shared_ptr<std::vector<std::string>> Request(const std::string& wmiNamespace,
        const std::string& wmiClass, const std::vector<std::string>& objectFields);

private:

    /// \brief метод подключения к wmi
    void connectToWmi(const std::string& wmiNamespace);

    void disonnectWmi();

    /// \brief флаг подключения к wmi
    bool wmiConnected_;

    /// \brief текущий неймспейс используемый в wmi
    std::string currentWmiNamespace_;

    /// \brief служба wmi к которой обрщаются запросы
    IWbemServices* service_;

    /// \brief подключение к пространству имет wmi
    IWbemLocator* locator_;

};

}

#endif