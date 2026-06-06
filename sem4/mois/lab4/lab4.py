import asyncio
import random
from spade.agent import Agent
from spade.behaviour import CyclicBehaviour, PeriodicBehaviour
from spade.message import Message
from spade.template import Template


class CourierAgent(Agent):
    class DeliveryBehaviour(CyclicBehaviour):
        async def run(self):
            msg = await self.receive(timeout=5)
            if msg:
                order_details = msg.body
                sender = str(msg.sender).split('/')[0]
                print(f"[{self.agent.name}] Получен заказ: {order_details}")

                print(f"   -> [{self.agent.name}] Еду в точку выдачи...")
                await asyncio.sleep(random.uniform(1.0, 2.0))

                print(f"   -> [{self.agent.name}] Товар забрал, везу клиенту...")
                await asyncio.sleep(random.uniform(2.0, 4.0))

                print(f"[{self.agent.name}] Заказ '{order_details}' успешно доставлен!")

                reply = Message(to=sender)
                reply.set_metadata("performative", "inform")
                reply.body = f"ДОСТАВЛЕНО: {order_details}"
                await self.send(reply)

    async def setup(self):
        print(f"[{self.name}] Вышел на смену. Жду заказы.")
        template = Template()
        template.set_metadata("performative", "request")
        self.add_behaviour(self.DeliveryBehaviour(), template)


class DispatcherAgent(Agent):
    def __init__(self, jid, password, couriers):
        super().__init__(jid, password)
        self.couriers = couriers
        self.order_counter = 1

    class GenerateOrdersBehaviour(PeriodicBehaviour):
        async def run(self):
            order_name = f"Заказ #{self.agent.order_counter} (Пицца и Кола)"
            self.agent.order_counter += 1

            chosen_courier = random.choice(self.agent.couriers)

            print(f"\n[Диспетчер] Поступил новый {order_name}. Назначаю курьера: {chosen_courier}")

            msg = Message(to=chosen_courier)
            msg.set_metadata("performative", "request")
            msg.body = order_name
            await self.send(msg)

    class ReceiveReportsBehaviour(CyclicBehaviour):
        async def run(self):
            msg = await self.receive(timeout=10)
            if msg:
                print(f"[Диспетчер] Получен отчет: {msg.body}")

    async def setup(self):
        print(f"[{self.name}] Диспетчерская запущена.")

        gen_b = self.GenerateOrdersBehaviour(period=4)
        self.add_behaviour(gen_b)

        rep_b = self.ReceiveReportsBehaviour()
        template = Template()
        template.set_metadata("performative", "inform")
        self.add_behaviour(rep_b, template)


async def main():
    disp_jid = "manager_42170053@xmpp.jp"
    courier1_jid = "worker1_42170053@xmpp.jp"
    courier2_jid = "worker2_42170053@xmpp.jp"
    password = "123123"

    courier1 = CourierAgent(courier1_jid, password)
    courier2 = CourierAgent(courier2_jid, password)

    dispatcher = DispatcherAgent(disp_jid, password, couriers=[courier1_jid, courier2_jid])

    await courier1.start(auto_register=False)
    await courier2.start(auto_register=False)
    await asyncio.sleep(2)
    await dispatcher.start(auto_register=False)

    await asyncio.sleep(20)

    print("\nЗавершение смены...")
    await courier1.stop()
    await courier2.stop()
    await dispatcher.stop()


if __name__ == "__main__":
    asyncio.run(main())