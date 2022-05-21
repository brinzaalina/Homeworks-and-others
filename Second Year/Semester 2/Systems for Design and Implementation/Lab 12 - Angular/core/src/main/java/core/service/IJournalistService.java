package core.service;

import core.domain.JournalistEntity;

import java.util.Date;
import java.util.List;

public interface IJournalistService {
    List<JournalistEntity> getAllJournalists();
    void addJournalist(String lastName, String firstName, String email, Date dob);
    void deleteJournalist(Long id);
    void updateJournalist(Long id, String lastName, String firstName, String email, Date dob);
    List<JournalistEntity> getAllJournalistsBornBefore(Date date);
}
