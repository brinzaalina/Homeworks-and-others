package core.repository;

import core.domain.JournalistEntity;

import java.util.Date;
import java.util.List;

public interface IJournalistRepository extends IRepository<JournalistEntity, Long> {
    List<JournalistEntity> findJournalistEntitiesByDobBefore(Date date);
}
