from experta import Fact, KnowledgeEngine, Rule, NOT, MATCH


class Defect(Fact):
    """Показатели диагностики."""
    pass


class Diagnosis(Fact):
    """Диагноз."""
    pass


class DiagnosisEngine(KnowledgeEngine):
    @Rule(NOT(Defect(name='пробег')))
    def ask_mileage(self):
        value = input("Пробег в км:\n1. <30000\n2. 30000-100000\n3. 100000-500000\n4. >500000\nВведите чсило: ").strip().lower()
        self.declare(Defect(name='пробег', value=value))

    @Rule(NOT(Defect(name='шум')))
    def ask_noise(self):
        value = input("Шумы (нет / стук двигателя / скрип подвески / неизвестно): ").strip().lower()
        self.declare(Defect(name='шум', value=value))

    @Rule(NOT(Defect(name='индикатор')))
    def ask_panel(self):
        value = input("Индикатор на приборной панели (нет / бензин / чек / жидкость стеклоочистителя / неизвестно): ").strip().lower()
        self.declare(Defect(name='индикатор', value=value))

    @Rule(
        Defect(name='индикатор', value='чек'),
        Defect(name='шум', value='стук двигателя')
    )
    def engine_critical(self):
        self.declare(Diagnosis(name='поломка_двигателя'))
        print("Предположительный дефект: Критическая поломка ДВС.")
        print("Решение: Заглушите двигатель и вызывайте эвакуатор.")

    @Rule(
        Defect(name='шум', value='скрип подвески'),
        Defect(name='индикатор', value='нет') | Defect(name='индикатор', value='неизвестно')
    )
    def suspension_issue(self):
        self.declare(Diagnosis(name='износ_подвески'))
        print("Предположительный дефект: Износ деталей ходовой части (сайлентблоки, шаровые).")
        print("Решение: Требуется осмотр подвески на СТО.")

    @Rule(
        Defect(name='индикатор', value='бензин')
    )
    def low_fuel(self):
        self.declare(Diagnosis(name='пустой_бак'))
        print("Состояние: Критически низкий уровень топлива.")
        print("Решение: Ближайшая АЗС.")

    @Rule(
        Defect(name='индикатор', value='жидкость стеклоочистителя')
    )
    def washer_fluid(self):
        self.declare(Diagnosis(name='нет_омывайки'))
        print("Состояние: Закончилась стеклоомывающая жидкость.")
        print("Решение: Долейте жидкость в бачок под капотом.")

    @Rule(
        Defect(name='индикатор', value='чек'),
        Defect(name='шум', value='нет') | Defect(name='шум', value='неизвестно'),
        Defect(name='пробег', value='3') | Defect(name='пробег', value='4')
    )
    def old_car_check(self):
        self.declare(Diagnosis(name='ошибка_электроники_или_экологии'))
        print("Предположительный дефект: Ошибка датчиков из-за большого пробега.")
        print("Решение: Требуется компьютерная диагностика сканером OBD2.")

    @Rule(
        Defect(name='шум', value='нет'),
        Defect(name='индикатор', value='нет'),
        Defect(name='пробег', value='1') | Defect(name='пробег', value='2'),
        NOT(Diagnosis())
    )
    def car_healthy(self):
        self.declare(Diagnosis(name='исправен'))
        print("Состояние: Автомобиль полностью исправен. Дефектов не выявлено.")

    @Rule(
        Defect(name='пробег', value=MATCH.p),
        Defect(name='шум', value=MATCH.n),
        Defect(name='индикатор', value=MATCH.i),
        NOT(Diagnosis()),
        salience=-10
    )
    def unknown_defect(self, p, n, i):
        print("Не удалось определить конкретный дефект по введенным данным.")
        print(f"Зафиксировано: пробег={p}, шумы={n}, индикатор={i}")


if __name__ == "__main__":
    engine = DiagnosisEngine()
    engine.reset()
    engine.run()
