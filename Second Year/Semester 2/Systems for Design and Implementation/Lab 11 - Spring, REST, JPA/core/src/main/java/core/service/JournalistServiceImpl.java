package core.service;

import core.domain.JournalistEntity;
import core.domain.validators.JournalistValidator;
import core.exceptions.NewsException;
import core.repository.IJournalistRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Date;
import java.util.List;

@Service
public class JournalistServiceImpl implements IJournalistService {
    public static final Logger logger = LoggerFactory.getLogger(JournalistServiceImpl.class);

    @Autowired
    private JournalistValidator validator;

    @Autowired
    private IJournalistRepository journalistRepository;

    @Override
    public List<JournalistEntity> getAllJournalists() {
        logger.trace("getAllJournalists - method entered");
        List<JournalistEntity> journalists = journalistRepository.findAll();
        logger.trace("getAllJournalists: " + journalists);
        return journalists;
    }

    @Override
    public void addJournalist(String lastName, String firstName, String email, Date dob) {
        logger.trace("addJournalist - method entered - lastName: " + lastName + ", firstName: " + firstName + ", email: " + email + ", dob: " + dob);
        JournalistEntity journalist = new JournalistEntity(lastName, firstName, email);
        journalist.setDob(dob);
        validator.validate(journalist);
        journalistRepository.save(journalist);
        logger.trace("addJournalist - method finished");
    }

    @Override
    public void deleteJournalist(Long id) {
        logger.trace("deleteJournalist - method entered - id: " + id);
        journalistRepository.findById(id)
                .ifPresentOrElse((journalist) -> journalistRepository.deleteById(journalist.getId()),
                        () -> {
                            throw new NewsException("Journalist does not exist!");
                        });
        logger.trace("deleteJournalist - method finished");
    }

    @Override
    @Transactional
    public void updateJournalist(Long id, String lastName, String firstName, String email, Date dob) {
        logger.trace("updateJournalist - method entered - id: " + id + ", lastName: " + lastName + ", firstName: " + firstName + ", email:" + email + ", dob: " + dob);
        JournalistEntity journalistEntity = new JournalistEntity(lastName, firstName, email);
        journalistEntity.setId(id);
        journalistEntity.setDob(dob);
        validator.validate(journalistEntity);
        journalistRepository.findById(id)
                .ifPresentOrElse((journalist) -> {
                    journalist.setLastName(lastName);
                    journalist.setFirstName(firstName);
                    journalist.setEmail(email);
                    journalist.setDob(dob);
                }, () -> {
                    throw new NewsException("Journalist does not exist!");
                });
        logger.trace("updateJournalist - method finished");
    }

    @Override
    public List<JournalistEntity> getAllJournalistsBornBefore(Date date) {
        logger.trace("getAllJournalistsBornBefore - method entered; date = {}",  date);
        List<JournalistEntity> journalistsBornBefore = journalistRepository.findJournalistEntitiesByDobBefore(date);
        logger.trace("getAllJournalistsBornBefore - method finished; result = {}", journalistsBornBefore);
        return journalistsBornBefore;
    }
}
