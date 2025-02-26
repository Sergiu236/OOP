#include "repository.h"
#include <iostream>

void Repository::load_data() {
    std::ifstream file(doctorFile);
    std::string name, specialisation;
    std::string line;
    char sep = '|';
    while (getline(file, line)) {
        std::stringstream ss(line);
        getline(ss, name, sep);
        getline(ss, specialisation, sep);
        doctors.push_back(Doctor(name, specialisation));
    }
    file.close();

    file.open(patientFile);
    std::string diagnosis, doctor, date;
    while (getline(file, line)) {
        std::stringstream ss(line);
        getline(ss, name, sep);
        getline(ss, diagnosis, sep);
        getline(ss, specialisation, sep);
        getline(ss, doctor, sep);
        getline(ss, date, sep);
        patients.push_back(Patient(name, diagnosis, specialisation, doctor, date));
    }
    file.close();
}

void Repository::savePatientsToFile() const {
    std::ofstream file(patientFile);
    for (const auto& patient : patients) {
        file << patient.getName() << "|"
             << patient.getDiagnosis() << "|"
             << patient.getSpecialisation() << "|"
             << patient.getDoctor() << "|"
             << patient.getDate() << "\n";
    }
    file.close();
}