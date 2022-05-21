package web.controller;

import core.domain.JournalistEntity;
import core.service.IJournalistService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import web.converter.JournalistConverter;
import web.dto.JournalistDTO;
import web.dto.JournalistsDTO;

import java.util.Date;
import java.util.List;

@RestController
public class JournalistController {
    public static final Logger logger = LoggerFactory.getLogger(JournalistController.class);

    @Autowired
    private IJournalistService journalistService;

    @Autowired
    private JournalistConverter journalistConverter;

    @RequestMapping(value = "/journalists")
    JournalistsDTO getJournalistsFromRepository() {
        logger.trace("getAllJournalists - method entered");
        List<JournalistEntity> journalists = journalistService.getAllJournalists();
        JournalistsDTO journalistsDTO = new JournalistsDTO(journalistConverter.convertModelsToDTOs(journalists));
        logger.trace("getAllJournalists: " + journalists);
        return journalistsDTO;
    }

    @RequestMapping(value = "/journalists", method = RequestMethod.POST)
    void addUser(@RequestBody JournalistDTO journalistDTO) {
        logger.trace("addJournalist - method entered - journalistDTO: " + journalistDTO);
        var journalist = journalistConverter.convertDtoToModel(journalistDTO);
        journalistService.addJournalist(journalist.getLastName(), journalist.getFirstName(), journalist.getEmail(), journalist.getDob());
        logger.trace("addJournalist - journalist added");
    }

    @RequestMapping(value = "/journalists/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteJournalist(@PathVariable Long id) {
        journalistService.deleteJournalist(id);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @RequestMapping(value = "/journalists/{id}", method = RequestMethod.PUT)
    void updateJournalist(@PathVariable Long id, @RequestBody JournalistDTO journalistDTO) {
        logger.trace("updateJournalist - method entered - journalistDTO: " + journalistDTO);
        var journalist = journalistConverter.convertDtoToModel(journalistDTO);
        journalistService.updateJournalist(id, journalist.getLastName(), journalist.getFirstName(), journalist.getEmail(), journalist.getDob());
        logger.trace("updateJournalist - journalist updated");
    }

    @RequestMapping(value = "/journalists/filter/{date}")
    JournalistsDTO getAllJournalistsBornBefore(@PathVariable @DateTimeFormat(pattern = "d-M-yyyy") Date date) {
        return new JournalistsDTO(journalistConverter.convertModelsToDTOs(journalistService.getAllJournalistsBornBefore(date)));
    }
}
