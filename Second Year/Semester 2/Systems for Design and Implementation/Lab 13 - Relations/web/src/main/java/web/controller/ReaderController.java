package web.controller;

import core.domain.JournalistEntity;
import core.domain.ReaderEntity;
import core.service.IJournalistService;
import core.service.IReaderService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import web.converter.ReaderConverter;
import web.dto.ReaderDTO;
import web.dto.ReadersDTO;

import java.util.List;

@RestController
public class ReaderController {
    public static final Logger logger = LoggerFactory.getLogger(ReaderController.class);

    @Autowired
    private IReaderService readerService;

    @Autowired
    private ReaderConverter readerConverter;

    @RequestMapping(value = "/readers")
    ReadersDTO getReadersFromRepository() {
        logger.trace("getReadersFromRepository - method entered");
        List<ReaderEntity> readers = readerService.getAllReaders();
        ReadersDTO readersDTO = new ReadersDTO(readerConverter.convertModelsToDTOs(readers));
        logger.trace("getReadersFromRepository: " + readers);
        return readersDTO;
    }

    @RequestMapping(value = "/readers", method = RequestMethod.POST)
    void addReader(@RequestBody ReaderDTO readerDTO) {
        logger.trace("addReader - method entered - readerDTO: " + readerDTO);
        var reader = readerConverter.convertDtoToModel(readerDTO);
        readerService.addReader(reader.getLast_name(), reader.getFirst_name(), reader.getContact());
        logger.trace("addReader - journalist added");
    }

    @RequestMapping(value = "/readers/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteReader(@PathVariable Long id) {
        readerService.deleteReader(id);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @RequestMapping(value = "/readers/{id}", method = RequestMethod.PUT)
    void updateReader(@PathVariable Long id, @RequestBody ReaderDTO readerDTO) {
        logger.trace("updateReader - method entered - readerDTO: " + readerDTO);
        var reader = readerConverter.convertDtoToModel(readerDTO);
        readerService.updateReader(id, reader.getLast_name(), reader.getFirst_name(), reader.getContact());
        logger.trace("updateReader - journalist updated");
    }
}
