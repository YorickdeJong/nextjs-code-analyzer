'use client'
import Image from "next/image";
import Link from "next/link";
import { useRouter } from "next/navigation";
import { useEffect, useState } from "react";
import { Images } from "@/components/images";
import { Typography } from "@/components/ui/typography";
import { inter, openSans } from "@/lib/fonts";
import Gegevens from "./gegevens";
import Amount from "./amount";
import SportMaatje from "./SportMaatje";
import PaymentMethods from "./paymentMethods";
import Benefits from "./benefits";
import { Icons } from "@/components/icons";
import Countdown from "./Countdown";
import axios from "axios";
import * as yup from 'yup';
import { v4 as uuidv4 } from 'uuid';
import Script from "next/script";
import Banner from "./Banner";
import path from 'path';
import { TailSpin } from "react-loader-spinner";


export default function Checkout() {
  const [loading, setLoading] = useState(false);
  const [testing, useTesting] = useRouter(false);
  const [left, setState] = useState(false); 
    const orderId = uuidv4();
    const [countdownDone, setCountdownDone] = useState(false);
    const [formData, setFormData] = useState<FormData>({
      productName: 'Project 50',
      firstName: '',
      lastName: '',
      email: '',
      amount: 150,
      quantity: 1,
      sportMaatjes: [],
      paymentMethod: 'ideal',
      bank: '',
      orderId: orderId,
    });

    useEffect(() => {}, [])
    useEffect(() => {
      console.log('process.env.NEXT_PUBLIC_DASHBOARD_URL', process.env.NEXT_PUBLIC_DASHBOARD_URL);
      const incrementCounter = async () => {
        try {
          if (process.env.NEXT_PUBLIC_DASHBOARD_URL) {
            const response = await axios.post(`${process.env.NEXT_PUBLIC_DASHBOARD_URL}/api/increment-counter?page=${'Project 50 Nieuw Jaar'}`);
            console.log('Counter incremented', response.data);
          } else {
            console.log('Not in production environment or DASHBOARD_URL is not set');
          }
        } catch (error) {
          console.error('Failed to increment counter', error);
        }
      };
    
      incrementCounter();
    }, []);

    const handleChange = (e, index, field) => {

      // Handle string values (for paymentMethod updates).
      if (typeof e === 'string') {
        setFormData((prevFormData) => ({ ...prevFormData, paymentMethod: e }));
        return;
      }
      

      if (typeof e === 'number') {
        console.log('e', e)
        setFormData((prevFormData) => ({ ...prevFormData, amount: e }));
        return;
      }
    
      // Handle function values (for quantity updates)
      if (typeof e === 'function') {
        setFormData((prevFormData) => ({ ...prevFormData, quantity: e(prevFormData.quantity) }));
        return;
      }
    
      // Handle event objects from input changes
      if (e && e.target) {
        const { name, value, dataset } = e.target;
    
        // Handle sportMaatje updates
        if (typeof index === 'number' && field) {
          setFormData((prevFormData) => {
            const updatedSportMaatjes = [...prevFormData.sportMaatjes];
            updatedSportMaatjes[index] = {
              ...updatedSportMaatjes[index],
              [field]: value,
            };
            return { ...prevFormData, sportMaatjes: updatedSportMaatjes };
          });
          return;
        }
    
        // Handle other input changes
        setFormData((prevFormData) => ({ ...prevFormData, [name]: value }));
        return;
      }
    
      console.error('Unhandled change event:', e);
    };



    const handleSubmit = async (event ) => {
      event.preventDefault();
      setLoading(true);
      // await validateFormData();
      const amount = formData.amount.toString();
      const metadata = { 
        orderId: formData.orderId, 
        quantity: formData.quantity, 
        sportMaatjes: formData.sportMaatjes, 
        email: formData.email,
        firstName: formData.firstName,
        lastName: formData.lastName,
        free: false,
        amount: amount
      };
      const description = `Payment for ${formData.productName} - Order #${encodeURIComponent(formData.orderId)}`;
      try {
        const response = await axios.post('/api/molli', {
          amount,
          description,
          method: formData.paymentMethod,
          redirectUrl: process.env.NEXT_PUBLIC_REDIRECT_URL,
          webhookUrl: process.env.NEXT_PUBLIC_WEBHOOK_URL,
          metadata,
          issuer: formData.bank,
        });
    
        if (response.status === 200) {
          window.location.href = response.data._links.checkout.href;
        } else {
          console.error('Payment creation failed:', response.data);
          alert('Payment creation failed, please try again.');
        }
      } catch (error) {
        console.error('Payment creation failed:', error);
        alert('Payment creation failed, please try again.');
      }
    
      setLoading(false);
    };


     

    return (
      <>
        <Banner quantity={formData.quantity}/>
        <section className="bg-white grid grid-cols-1 lg:grid-cols-2 min-h-screen">
          
          <div className="h-[550px] relative">
              <div className="lg:h-screen lg:fixed lg:w-[50%]">
                <Images.checkout_bg  className = 'lg:hidden'/>
                <Images.checkout_bg_large  className = 'hidden lg:block'/>
                <div className="absolute inset-0 bg-dark/30" />
                <div className="absolute inset-0 mt-28 lg:mt-0 lg:top-[30%] ">
                  <Countdown 
                  setCountdownDone={setCountdownDone}
                  quantity={formData.quantity}
                  handleChange={handleChange}
                  />
                </div>
              </div>
          </div>

          <div className="flex flex-col py-8 lg:py-16 lg:mt-0 mx-8 lg:mx-16">
            <div className="">
              <Typography variant={'title'} className="text-xl lg:text-3xl font-bold leading-9 tracking-tight text-gray-900 font-impact ">
                Jouw <span className="text-secondary">droom</span> transformatie in 50 dagen
              </Typography>

              <Typography variant = 'muted' className="mt-2 text-md text-[#242424] lg:text-[18px] leadng-8 lg:leading-7">
              Wat zou jij er voor over hebben als je <span className="font-bold">zeker</span> zou weten dat je al je doelen gaat bereiken? De €3 per dag is symbolisch voor jouw inzet. 
              Bij eerdere versies van project50 heb ik gezien dat de mensen die bereid zijn om in zichzelf te investeren ook het beste resultaat behalen.
              </Typography>
            </div>
          
                          
            <Benefits />


            {!countdownDone && <div className="mt-8 ">
              <form className="space-y-4" onSubmit={handleSubmit}>
                <Gegevens 
                  handleChange = {handleChange}
                  formData={formData}
                />
                
                <Amount
                  setQuantity={handleChange}
                  quantity={formData.quantity}
                />


                <SportMaatje 
                quantity = {formData.quantity}
                onChange = {handleChange}
                />
                
                <PaymentMethods 
                onChange = {handleChange}
                paymentMethod = {formData.paymentMethod}
                />

                <div>
                  <button
                    type="submit"
                    className={`flex w-full justify-center rounded-md bg-secondary px-3 py-3 text-md font-semibold leading-6 text-white shadow-sm hover:bg-primary focus-visible:outline focus-visible:outline-2 focus-visible:outline-offset-2 focus-visible:outline-indigo-600 ${inter.className}`}
                  >
                    {loading ? (
                      <TailSpin
                        color="#FFFFFF"
                        height={20}
                        width={20}
                      />
                    ) : (
                      <>
                        Afrekenen
                        <Icons.arrowDown className="-rotate-90 ml-2 lg:ml-8 h-4 w-5 mt-1" />
                      </>
                    )}
                  </button>
                </div> 
              </form>

              
            </div>
          }
          {
            countdownDone && <Typography variant={'title'} className="text-dark mt-16">De Inschrijvingen zijn gesloten</Typography>
          }
          </div>

        </section>

      </>

    )
  }
