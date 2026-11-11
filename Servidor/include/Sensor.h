#ifndef SENSOR_H
#define SENSOR_H
#include <string>
#include <ostream>
class Sensor {
protected:
    int id; std::string ubicacion; double lectura;
public:
    Sensor(int i,std::string u,double l);
    virtual ~Sensor();
    int getId() const;
    virtual void procesarLectura()=0;
    friend std::ostream& operator<<(std::ostream&,const Sensor&);
};
#endif
