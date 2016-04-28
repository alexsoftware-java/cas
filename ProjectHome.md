# Система контроля и управления доступом #

### Основное отличие от аналогичных систем: ###
  * работает со считывателями (через com- или usb-порт) и исполнительными устройствами (через pci-плату ценой ~100$) напрямую с ПК, без использования дорогостоящих контроллеров, что позволяет:
    * использовать существующую СКС (для связи между точками системы используется TCP/IP), избежав тем самым проведения специализированных линий связи (RS-485 и т.п.) для СКУД;
    * избежать ведения своей БД на каждом контроллере.
  * поставляется в исходных кодах со свободной лицензией (GPL v3), что позволяет:
    * не платить за лицензию на использование ПО;
    * не зависеть от фирмы-поставщика системы (в случае её ликвидации и т.п.);
    * бесплатно пользоваться доработками от других пользователей;
    * дорабатывать систему под свои нужды.

### При прикосновении карточкой к считывателю система производит следующие действия: ###
  * вывод на экран информации о владельце карточки (ФИО, фото, подразделение) для визуального сравнения охранником с человеком, приложившим карточку;
  * выдача информации о разрешении/запрещении прохода на основании информации из базы данных (имеется ли карточка в БД, действительна ли карточка, срок действия карточки, разрешен ли проход в данную зону данной карточке);
  * выдача команды исполнительному устройству (турникету, замку, шлагбауму);
  * запись о проходе/попытки прохода в лог.

### Другие модули: ###
  * ведение иерархической системы отделов любого уровня глубины;
  * заполнение и просмотр полей личной карточки каждого человека, введенного в систему;
  * задание и контроль прав доступа для работающего с системой пользователя;
  * печать карточек на карточном и обычном принтерах, с настройкой шаблона содержания карточки и шаблона расположения карточек на странице;
  * заказ временных пропусков удалённо (через html-страницу с авторизацией);
  * выдача временных пропусков с занесением в БД графических данных по посетителю (его фото, скан его паспорта и т.п.);
  * отправка SMS при входе и выходе указанного человека на заданный для него номер;
  * модуль <Графики>, позволяющий гибко задавать дни и время работы сотрудников и/или доступа в определённое помещение;
  * АРМ <Столовая> для предоставления указанной скидки сотрудникам определённого подразделения;
  * АРМ <Управление ключами> для организации выдачи и сдачи ключей;
  * генерация различных отчётов за произвольный период времени для любого подразделения на основе лога о событиях (проходах, запусках программы, предоставленных скидках, выданных ключах и т.п.).

### Работает ###
  * под управлением MS Windows 98/2000/XP/Vista/7 (и, вероятно, более новых);
  * с использованием SQL-сервера Firebird.

### Компиляция: ###
  * C++ Builder 6
  * библиотека генератора отчётов PReport

### Документы ###
  * [Руководство пользователя СКД-Предприятие](http://cas.googlecode.com/files/CAS-Enterprise%20manual.doc)
  * [Проспект по СКД-Предприятие](http://cas.googlecode.com/files/CAS-Enterprise%20booklet.doc)
  * [Проспект по СКД-Школа](http://cas.googlecode.com/files/CAS-School%20booklet.doc)
  * Свидетельство об официальной регистрации программы для ЭВМ “CAS” № 2005613275

### Внедрено ###
  * в общей сложности более чем на 60 объектах (в основном, школах) по России (Воркута, Дмитров, Казань, Ленинградская область (Сертолово и др.), Москва, Московская область (Видное, Пушкино), Нижневартовск, Ростов-на-Дону, Санкт-Петербург, Сургут, Улан-Удэ и др.).