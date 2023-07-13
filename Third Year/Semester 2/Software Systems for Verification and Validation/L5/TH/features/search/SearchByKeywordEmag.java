package org.example.features.search;

import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.thucydides.core.annotations.Issue;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.junit.annotations.UseTestDataFrom;
import org.example.steps.serenity.EndUserStepsEmag;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom(value="src/test/resources/emag_test_data.csv")
public class SearchByKeywordEmag {
    @Managed(uniqueSession = true)
    public WebDriver webdriver;

    @Steps
    public EndUserStepsEmag anna;

    public String name;

    public String filter;

    public WebDriver getWebdriver() {
        return webdriver;
    }

    public void setWebdriver(WebDriver webdriver) {
        this.webdriver = webdriver;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getFilter() {
        return filter;
    }

    public void setFilter(String filter) {
        this.filter = filter;
    }

    @Issue("#EMAG-1")
    @Test
    public void searchEmagByKeywordTestDDT() {
        anna.is_the_home_page();
        anna.looks_for(getName());
        if (getFilter().isEmpty()) {
            anna.should_see_products(getName());
        } else {
            anna.filter_products(getFilter());
        }
    }
}
