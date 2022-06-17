package core.service;

import core.domain.ReaderEntity;
import core.domain.ContactEntity;
import core.exceptions.NewsException;
import core.repository.IReaderRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class ReaderServiceImpl implements IReaderService{
    public static final Logger logger = LoggerFactory.getLogger(ReaderServiceImpl.class);

    @Autowired
    private IReaderRepository readerRepository;

    @Override
    public List<ReaderEntity> getAllReaders() {
        logger.trace("getAllReaders - method entered");
        List<ReaderEntity> readers = readerRepository.findAll();
        logger.trace("getAllReaders: " + readers);
        return readers;
    }

    @Override
    public void addReader(String lastName, String firstName, ContactEntity contact) {
        logger.trace("addReader - method entered - lastName: " + lastName + ", firstName: " + firstName + ", contact: " + contact);
        ReaderEntity reader = new ReaderEntity(lastName, firstName, contact);
        readerRepository.save(reader);
        logger.trace("addReader - method finished");
    }

    @Override
    public void deleteReader(Long id) {
        logger.trace("deleteReader - method entered - id: " + id);
        readerRepository.findById(id)
                .ifPresentOrElse((reader) -> readerRepository.deleteById(reader.getId()),
                        () -> {
                            throw new NewsException("Reader does not exist!");
                        });
        logger.trace("deleteReader - method finished");
    }

    @Override
    @Transactional
    public void updateReader(Long id, String lastName, String firstName, ContactEntity contact) {
        logger.trace("updateReader - method entered - id: " + id + ", lastName: " + lastName + ", firstName: " + firstName + ", contact: " + contact);
        readerRepository.findById(id)
                .ifPresentOrElse((reader) -> {
                    reader.setLast_name(lastName);
                    reader.setFirst_name(firstName);
                    reader.setContact(contact);
                }, () -> {
                    throw new NewsException("Reader does not exist!");
                });
        logger.trace("updateReader - method finished");
    }
}
