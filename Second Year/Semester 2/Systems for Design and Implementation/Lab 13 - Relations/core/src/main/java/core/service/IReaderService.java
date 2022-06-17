package core.service;

import core.domain.ReaderEntity;
import core.domain.ContactEntity;

import java.util.List;

public interface IReaderService {
    List<ReaderEntity> getAllReaders();
    void addReader(String lastName, String firstName, ContactEntity contact);
    void deleteReader(Long id);
    void updateReader(Long id, String lastName, String firstName, ContactEntity contact);
}
