export class LogPost {
    type: string | undefined;
    severity: string | undefined;
    date: string | undefined;
    logtext: string | undefined;

    constructor(type: string, severity: string, date: string, logtext:string) {
        this.type = type;
        this.severity = severity;
        this.date = date;
        this.logtext = logtext;
    }
  }